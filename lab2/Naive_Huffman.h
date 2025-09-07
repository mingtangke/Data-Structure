#ifndef NAIVE_HUFFMAN_H 
#define NAIVE_HUFFMAN_H
#include "ulity.h"
class Huffman_Operator{
public:
    typedef struct{
        double weight;
        int parent;
        int lchild;
        int rchild;
    }HTNode;

    typedef struct{
        int weight;
        char data;
        std::string HC;
    }Dictionary;

    std::string buffer,huffman_buffer,decode_buffer,recover;
    std::vector<Dictionary>Diction;
    std::vector<HTNode>Huffman_Tree;
    int leaf_num;
    int node_num;
    int total;

    Huffman_Operator(){
    }
    ~Huffman_Operator(){
    }

    virtual void Encode_Huffman(){
        int root = node_num ;
        for(int i = 1;i <= leaf_num;i++){
            int current = i;
            while(current != root){
                std::string code;
                int parent = Huffman_Tree[current].parent;
                code =  Huffman_Tree[parent].lchild == current ? "0":"1";
                Diction[i].HC += code;
                current = parent;
            }
            std::reverse(Diction[i].HC.begin(), Diction[i].HC.end());
        }
        /*for(int i=1;i<=leaf_num;i++){
            std::cout<<Huffman_Tree[i].weight<<" "<<Huffman_Tree[i].parent
            <<" "<<Huffman_Tree[Huffman_Tree[i].parent].lchild<<std::endl;
        }*/
    }

    virtual void Decode(){
        int root = node_num;
        size_t i = 0;
        while(i < decode_buffer.size()){
            int current = root;
            while(Huffman_Tree[current].lchild||Huffman_Tree[current].rchild){
               int child = decode_buffer[i] == '0' ? Huffman_Tree[current].lchild : Huffman_Tree[current].rchild;
               current = child;
               i++;
            }
            recover += Diction[current].data;
        }
        std::cout<<recover<<std::endl;
        if(recover == buffer) std::cout<<"Succeed to recover!"<<std::endl;
    }

    virtual void conclusion(){
        int add = 8 - decode_buffer.size() % 8;
        double rate = 1- (decode_buffer.size() + add + 8)/(8.0*buffer.size());
        std::cout<<"compression ratio :"<<rate<<std::endl;
    }
    virtual void Create_Huffman(){
        Inital_Huffman();
        if(leaf_num <= 1) return;
        int pos1,pos2;
        for(int i = leaf_num + 1; i <= node_num; i++){
            Select_Two(pos1,pos2,i-1);
            Huffman_Tree[pos1].parent = i;
            Huffman_Tree[pos2].parent = i;
            HTNode compact;
            compact.weight = Huffman_Tree[pos1].weight + Huffman_Tree[pos2].weight;
            compact.lchild = pos1;
            compact.rchild = pos2;
            compact.parent = 0;
            Huffman_Tree.push_back(compact);
        }
    }

    virtual void Generate_Huffman_Code(){
        ReadFile();
        Caculate_Weight();
        Create_Huffman();
        Encode_Huffman();
        Display_Huffman_Code("Naive_Compression_Dictionary.txt");
        Display_File_With_Huffman("File_With_Huffman.txt");
        Save_Bin_File();
        Read_Bin_File();
        Decode();
        conclusion();
    }
protected:
    virtual inline void Read_Bin_File(){
        std::ifstream readFile("Naive_Compact_File.bin",std::ios::binary);
        if(!readFile.is_open()){
            std::cerr<<"Fail to open Naive_Compact_File.bin"<<std::endl;
        }
        std::string bin_buffer;
        unsigned char temp;
        int add;
        readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        add = static_cast<int>(temp);
        while(readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
            bin_buffer += std::bitset<8>(temp).to_string();
        }
        for(int k = 0;k<add;k++){
            bin_buffer.pop_back();
        }
        if(bin_buffer == decode_buffer){
            std::cout<<"Succeed to recover from bin_file"<<std::endl;
            decode_buffer.clear();
            decode_buffer = bin_buffer;
        }
        readFile.close();
    }
 
    virtual inline void Save_Bin_File(){
        Read_Huffman_File("File_With_Huffman.txt");
        int add = 8 - decode_buffer.size()%8;
        for(int i = 0; i<add; i++){
            decode_buffer += "0";
        }

        std::ofstream outputFile("Naive_Compact_File.bin", std::ios::binary);
        if (!outputFile.is_open()) {
        throw std::logic_error("Failed to open Naive_Compact_File.bin");
        }

        std::string compact_buffer;
        unsigned char temp = static_cast<unsigned char>(add);
        outputFile.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        for(size_t i = 0;i <decode_buffer.size(); i+=8){
           compact_buffer = decode_buffer.substr(i,8);
           unsigned char byte = static_cast<unsigned char>(std::bitset<8>(compact_buffer).to_ulong());
           outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
           compact_buffer.clear();
        }

        for(int i = 0; i <add; i++){
           decode_buffer.pop_back();
        }
        outputFile.close();
    }


    virtual inline void Display_File_With_Huffman(std::string address){
        for(int i = 0;i < total; i++){
            for(int j = 1;j <= leaf_num;j++){
                if(Diction[j].data == buffer[i]){
                   huffman_buffer = huffman_buffer + Diction[j].HC;
                }
            }
        }

        std::ofstream outFile(address);
        if(outFile.is_open()){
            outFile << huffman_buffer;
            outFile.close();
        }
    }

    virtual inline void Display_Huffman_Code(std::string address){
        std::ofstream outFile(address);
        if(outFile.is_open()){
            outFile<<"ELment  Huffman_Code Freqency "<<std::endl;
            for(int i = 1;i <= leaf_num ;i++){
            outFile<<Diction[i].data<<"       "<<Diction[i].HC<<"     "
            <<1.0*Diction[i].weight/total<<std::endl;
        }
            outFile.close();
            std::cout<<"Succeed to save the Huffman_code"<<std::endl;
        }
        
    }
    
    virtual inline void Read_Huffman_File(std::string address){
        std::ifstream inputFile(address);
        if(!inputFile) std::cerr<<"Fail to open the file"<<std::endl;
        std::string line;
        while(std::getline(inputFile,line)){
            decode_buffer += line;
        }
        //std::cout<<"After read"<<decode_buffer.size();
        inputFile.close();
    }

    virtual inline void ReadFile(){
        std::ifstream inputFile("E:\\HomeWork\\lab2\\Life.txt");
        if(!inputFile) std::cerr<<"Fail to open the file"<<std::endl;
        std::string line;
        while(std::getline(inputFile,line)){
            buffer+=line;
        }
        inputFile.close();
        total = buffer.size();
        //std::cout<<buffer<<std::endl;
    }
    
	virtual inline void Caculate_Weight() {
	    Diction.push_back({-1,'@',""});
        for(int i = 0;i < static_cast<int>(buffer.size()); i++){
             bool find = false;
            for(std::vector<Dictionary>::iterator it = Diction.begin();it!=Diction.end();it++){
                if(it->data == buffer[i] && it->weight != -1){
                    it->weight++;
                    find = true;
                    break;
                }
            }
            if(!find) Diction.push_back({1,buffer[i],""});
        }
	    leaf_num = static_cast<int>(Diction.size())-1;
	    node_num = 2 * leaf_num - 1;
	}


    virtual inline void Inital_Huffman(){
        Huffman_Tree.push_back({0,0,0,0});
        for(int i = 1;i <= leaf_num;i++){
            HTNode node;
            node.lchild = 0;
            node.rchild = 0;
            node.parent = 0;
            node.weight = Diction[i].weight;
            Huffman_Tree.push_back(node);
        }
        /*for(int i = 1;i<=leaf_num;i++){
            std::cout<<Huffman_Tree[i].weight<<" ";
        }*/
    }

    virtual inline void Select_Two(int &min1,int &min2,int upper){
        for(int i = 1; i <= upper; i++){
            if(Huffman_Tree[i].parent == 0){
                min1 = i;
                break;
            }
        }
        for(int i = 1; i <= upper; i++){
            if(Huffman_Tree[min1].weight>Huffman_Tree[i].weight && Huffman_Tree[i].parent == 0){
                min1 = i;
            }
        }
        for(int j = 1; j <= upper; j++){
            if(Huffman_Tree[j].parent == 0 && j!=min1){
                min2 = j;
                break;
            }
        }
        for(int j = min2; j <= upper; j++){
            if(Huffman_Tree[min2].weight>Huffman_Tree[j].weight && Huffman_Tree[j].parent == 0 && j!=min1){
                min2 = j;
            }
        }
    }
};

#endif


// int main(void)
// {
//     Huffman_Operator hf;
//     hf.Generate_Huffman_Code();
//     return 0;
// }

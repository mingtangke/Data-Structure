
#include "ulity.h"
#include "Naive_Huffman.h"
#include "Heap_Sort.h"

class K_Ray_Huffman_Operator:public Huffman_Operator{
public:
    // int leaf_num;//直接用父亲的，不必重新定义了
    // int node_num;
    // int total;
    int size = 0,bit_num = 0;
    int system;
    int node_num = 0;
    int used_leaf_num = 0;
 
    // typedef struct{
    //     int weight;
    //     char data;
    //     std::string HC;
    // }Dictionary;
   
    // std::string buffer,huffman_buffer,decode_buffer,recover;
    // std::vector<Dictionary>Diction;
    std::vector<K_HTNode>Huffman_Tree;
    std::vector<int>root;
    
    K_Ray_Huffman_Operator(int k):Huffman_Operator(),system(k){}
    ~K_Ray_Huffman_Operator(){}


    void Generate_Huffman_Code(){
        Huffman_Operator::ReadFile();
        Huffman_Operator::Caculate_Weight();//bug 子定义的Diction会隐藏父类,不要再重新定义子变量
        Create_Huffman();
        Encode_Huffman();
        Display_File_With_Huffman();
        Huffman_Operator::Display_Huffman_Code("K_Ray_Compression_Dictionary.txt");
        //Huffman_Operator::Read_Huffman_File("E:\\HomeWork\\lab2\\output\\File_With_K_Ray_Huffman.txt");
        Save_Bin_File();
        Read_Bin_File();
        Decode();
        conclusion();
    }

    
    virtual void Decode()override{
        int root = node_num;
        size_t i = 0;

        while(i < decode_buffer.size()){
            int current = root;
            while(Check_Child(current)){
                for(int j = 0; j < static_cast<int>(Huffman_Tree[current].relation.size()); j++){
                    if(j+'0' == decode_buffer[i]){
                        int child = Huffman_Tree[current].relation[j];
                        current = child;
                        i++;
                        break;
                        }
                }
            }
            recover += Diction[current].data;
        }
        std::cout<<recover<<std::endl;
        if(recover == buffer) std::cout<<"Succeed to recover!"<<std::endl;
    }

    void Display_File_With_Huffman() {
        for(int i = 0;i < total; i++){
            for(int j = 1;j <= leaf_num;j++){
                if(Diction[j].data == buffer[i]){
                   huffman_buffer = huffman_buffer + Diction[j].HC;
                }
            }
        }
        std::ofstream outFile("File_With_K_Ray_Huffman.txt");
        if(outFile.is_open()){
            outFile << huffman_buffer;
            outFile.close();
            std::cout<<"Succeed to save the K_Ray_Huffman_code"<<std::endl;
        }
    }

    void Encode_Huffman()override{
        for(int i = 1;i <= leaf_num;i++){
            //std::cout<<"leaf:"<<i<<" "<<std::endl;
            int current = i;
            while(current != node_num){
                std::string code;
                int parent = Huffman_Tree[current].parent;
                for(size_t j=0;j < Huffman_Tree[parent].relation.size();j++){
                    if(Huffman_Tree[parent].relation[j] == current ) {
					code = std::to_string(j);
                    Diction[i].HC += code;
                    }
                }
                //std::cout<<current<<" ";
                current = parent;
            }
            std::reverse(Diction[i].HC.begin(), Diction[i].HC.end());
        }
    }

    void Create_Huffman()override{
        Inital_Huffman();
        if(leaf_num <= 1) return;

        int real_pos;
        std::vector<std::vector<int>>result;
        Get_K_Min(Huffman_Tree,result,system);

        for(size_t i = 0; i<result.size(); i++){
            K_HTNode addition;
            addition.parent = 0;
            addition.real_pos = Huffman_Tree.size();
            //std::cout<<"addition.real_pos"<<addition.real_pos;
            //std::cout<<"Huffman_Size"<<Huffman_Tree.size();
            addition.weight = 0;
            for(size_t j=0; j<result[i].size(); j++){
                real_pos = result[i][j];
                //std::cout<<real_pos<<count++<<" "<<Huffman_Tree.size()<<std::endl;
                //std::cout<<"***"<<Huffman_Tree[real_pos].parent<<std::endl;
                Huffman_Tree[real_pos].parent = addition.real_pos;//bug
                addition.weight += Huffman_Tree[real_pos].weight;
                addition.relation.push_back(real_pos);
            }
            Huffman_Tree.push_back(addition);
        }
        node_num = Huffman_Tree.size() - 1;
        //std::cout<<"node_num"<<" "<<node_num;
    }
    
protected:

    inline void Read_Bin_File()override{
        std::ifstream readFile("K_Ray_Compact_File.bin", std::ios::binary);
        if (!readFile.is_open()){
            std::cerr << "Fail to open K_Ray_Compact_File.bin" << std::endl;
        }
        std::string bin_buffer;
        unsigned char temp;
        int add;
        
        readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        add = static_cast<int>(temp);
        //bit_num ++;
        while (readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
            //bit_num ++;
            std::string sum;
            int value = static_cast<int>(temp);
            for (int i = 0; i<size; i++) {
                sum = std::to_string(value%system) + sum;
                value = value/system;
            }
            bin_buffer += sum;
        }
        //std::cout<<"bit_num"<<bit_num<<std::endl;

        for (int k = 0; k < add; k++) {
            bin_buffer.pop_back();
        }
        if (bin_buffer == decode_buffer) {
            std::cout << "Succeed to recover from bin_file" << std::endl;
            decode_buffer.clear();
            decode_buffer = bin_buffer;
        }
        readFile.close();
    }

    inline void Save_Bin_File() override {
        Huffman_Operator::Read_Huffman_File("File_With_K_Ray_Huffman.txt");
        size = std::floor(std::log2(256)/std::log2(system));
        int add = size - decode_buffer.size()%size;
        for (int i = 0; i<add; i++){
            decode_buffer += "0";
        }

        std::ofstream outputFile("K_Ray_Compact_File.bin", std::ios::binary);
        if (!outputFile.is_open()) {
            throw std::logic_error("Failed to open K_Ray_Compact_File.bin");
        }

        unsigned char temp = static_cast<unsigned char>(add);
        outputFile.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        bit_num++;
        for (size_t i = 0; i < decode_buffer.size(); i += size){
            std::string compact_buffer = decode_buffer.substr(i,size);
            int sum = 0;
            for(size_t k = 0; k<compact_buffer.size(); k++){
                sum = sum*system + (compact_buffer[k]-'0'); // 将K进制字符串转为整数
            }
            unsigned char byte = static_cast<unsigned char>(sum);
            outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
            bit_num++;
        }

        for (int i = 0; i < add; i++) {
            decode_buffer.pop_back();
        }
        outputFile.close();
    }
  
    inline bool Check_Child(int current){
        bool flag = false;
        for(size_t i = 0; i<Huffman_Tree[current].relation.size(); i++){
            if(Huffman_Tree[current].relation[i]) flag = true;
        }
        return flag;
    }

    inline void Inital_Huffman() override{
        //std::cout<<"The size of Diction"<<std::endl;

        for(int i = 0;i <= leaf_num;i++){
            K_HTNode node;
            node.weight = Diction[i].weight;
            node.real_pos = i;
            node.parent = -1;
            for(int j = 0; j <= system; j++){
                node.relation.push_back(0);
            }
            Huffman_Tree.push_back(node);
        }
        int add = 0;
        if(system > 2){
            add = system-leaf_num % (system-1);
            for(int k = leaf_num + 1; k <= leaf_num + add; k++){
                K_HTNode node;
                node.weight = 0;
                node.real_pos = k;
                node.parent = -1;
                Huffman_Tree.push_back(node);
            }
            used_leaf_num = add + leaf_num;
        }
        //std::cout<<"valid num"<<Huffman_Tree.size()-1<<std::endl;
    }
    inline void conclusion()override{
        double rate = 1-1.0*bit_num/(buffer.size());
        std::cout<<"compression ratio :"<<rate<<std::endl;
    }  
};

// int main(void){
//     K_Ray_Huffman_Operator kh(5);
//     kh.Generate_Huffman_Code();
//     return 0;
// }    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
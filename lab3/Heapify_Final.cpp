#include "ulity.h"
constexpr int MVINT = 10000;
class Mat_Graph_Operator{
public:
    typedef struct{
        char vex_name;
        int connected;
        int visited;
    }data;

    typedef struct{
        std::vector<data>vexs;
        std::vector<std::vector<int>>arcs;
    }Mat_Graph;

    typedef struct{
        int real_index;
        int adjvex_index;
        int lowcost;
    }Cost;

    typedef struct{
        int front_index;
        int rear_index;
        int lowcost;
    }edge;

    Mat_Graph MG;

    std::vector<Mat_Graph_Operator::Cost>cost;
    std::vector<edge>Edge;
    int vexnum,arcnum;

    Mat_Graph_Operator(int _vexnum,int _arcnum):vexnum(_vexnum),arcnum(_arcnum){
        Inital_Mat_Graph();
        Read_File_Generate_Mat();
    }
    virtual ~Mat_Graph_Operator(){}

    
    void Prime_Min_Span_Tree(bool apparent){
        if(apparent){
        std::cout<<"1.The Prime_Min_Span_Tree is :"<<std::endl;
        }
        cost.resize(vexnum);

        int center = 0;
        for(int i = 0; i<vexnum; i++){
            cost[i].adjvex_index = center;
            cost[i].real_index = i;
            cost[i].lowcost = center!=i ? MG.arcs[center][i]:0;
        }
        for(int k = 0; k<vexnum-1; k++){
            int next_index = Select_Min(cost);
            if(apparent){
            std::cout<<MG.vexs[next_index].vex_name<<MG.vexs[cost[next_index].adjvex_index].vex_name<<" "
            <<MG.arcs[next_index][cost[next_index].adjvex_index]<<std::endl;
            }

            cost[next_index].lowcost = 0;
            cost[next_index].adjvex_index = next_index;
            for(int i = 0; i<vexnum; i++){
                if(cost[i].lowcost!=0 && cost[i].lowcost > MG.arcs[i][next_index]){
                    cost[i].lowcost = MG.arcs[i][next_index];
                    cost[i].adjvex_index = next_index;
                }
            }
        }
        if(apparent) std::cout<<std::endl;
    }

    void Kruskal_Min_Span_Tree(){
        std::cout<<"3.The Kruskal_Min_Span_Tree is :"<<std::endl;

        int sum_distance = 0;
        for(int i = 0; i<vexnum ;i++){
            MG.vexs[i].connected = i;
        }
        for(int i = 0; i<vexnum; i++){
            for(int j = 0; j<=i; j++){
                 if(MG.arcs[i][j] != MVINT&&i!=j ){
                        Edge.push_back({i,j,MG.arcs[i][j]});
                    }
            }
        }
        Sort_Min_Edge();
        // for(int i = 0;i<arcnum;i++){
        //     std::cout<<Edge[i].lowcost<<" ";
        // }
        // std::cout<<std::endl;
        
        for(int i = 0; i<arcnum; i++){
            
            int v1 = Edge[i].front_index;
            int v2 = Edge[i].rear_index;
            int vs1 = MG.vexs[v1].connected;
            int vs2 = MG.vexs[v2].connected;
            
            if(vs1!=vs2){
            sum_distance += Edge[i].lowcost;
            std::cout<<MG.vexs[v1].vex_name<<MG.vexs[v2].vex_name<<" "<<Edge[i].lowcost<<std::endl;
            MG.vexs[v2].connected = vs1; 
            for(int j = 0; j<vexnum; j++){
                if(MG.vexs[j].connected == vs2) MG.vexs[j].connected = vs1;
                }  
            }
        }
        std::cout<<"The total distance is :"<<sum_distance<<std::endl;
    }

    void Measure_Heapify_Prime_Min_Span_Tree() {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i< 10*MVINT;i++) Heapify_Prime_Min_Span_Tree(false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Heapify_Prime_Min_Span_Tree took " << duration.count() << " seconds.\n";
    }

    void Measure_Prime_Min_Span_Tree() {
        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i< 10*MVINT;i++) Prime_Min_Span_Tree(false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Prime_Min_Span_Tree took " << duration.count() << " seconds.\n";
    }

    virtual void Mat_Graph_Control(){
        //Display_Mat_Graph();
        Prime_Min_Span_Tree(true);
        Heapify_Prime_Min_Span_Tree(true);
        Kruskal_Min_Span_Tree();
        Measure_Prime_Min_Span_Tree();
        Measure_Heapify_Prime_Min_Span_Tree();
    }

    void Heapify_Prime_Min_Span_Tree(bool apparent){
        if(apparent){
        std::cout<<"2.The Heapify_Prime_Min_Span_Tree is :"<<std::endl;
        }

        std::deque<Mat_Graph_Operator::Cost>virable_cost;
        std::vector<Mat_Graph_Operator::Cost>const_cost;
        int center = 0;

        for(int i = 0; i<vexnum; i++){
            int lowcost;
            if(i == 0) lowcost = 0;
            else lowcost = MG.arcs[center][i];
            virable_cost.push_back({i,0,lowcost});
            const_cost.push_back({i,0,lowcost});
        }
        virable_cost.pop_front();
        Bulid_Virable_Cost_Heap(virable_cost,virable_cost.size());
        //Print(virable_cost);

        for(int k = 0; k<vexnum-1; k++){
            //Print(virable_cost);
            int next_index = Get_Min_Index(virable_cost);
            //std::cout<<next_index<<" ";

            if(apparent){
            std::cout<<MG.vexs[next_index].vex_name<<MG.vexs[const_cost[next_index].adjvex_index].vex_name<<" "
            <<MG.arcs[next_index][const_cost[next_index].adjvex_index]<<std::endl;
            }

            //const_cost[next_index].adjvex_index = next_index;
        
            for(int i = 0; i<virable_cost.size();i++){
                if(virable_cost[i].lowcost > MG.arcs[virable_cost[i].real_index][next_index]){
                    const_cost[virable_cost[i].real_index].adjvex_index = next_index;
                    virable_cost[i].lowcost = MG.arcs[virable_cost[i].real_index][next_index];
                    virable_cost[i].adjvex_index = next_index;
                    Heapify_Float_Up(virable_cost,i);
                }
            }
        }
        if(apparent) std::cout<<std::endl;

    }


protected:

    inline void Heapify_Float_Up(std::deque<Cost> &virable_cost,int current){
        while(current > 0){
            int parent = (current-1)/2;
            if(virable_cost[parent].lowcost>virable_cost[current].lowcost){
                Swap(virable_cost[parent],virable_cost[current]);
            }
            else{
                break;
            }
        }
    }
    inline void Swap(Cost &cost1,Cost&cost2){
        Cost temp;
        temp = cost1;
        cost1 = cost2;
        cost2 = temp;
    }

    inline void Heapify(std::deque<Cost> &virable_cost,int size,int root){
        int small = root;
        int lchild = root*2+1;
        int rchild = root*2+2;
        if(lchild < size && virable_cost[small].lowcost>virable_cost[lchild].lowcost){
            small = lchild;
        } 
        if(rchild < size && virable_cost[small].lowcost>virable_cost[rchild].lowcost){
            small = rchild;
        }
        if(small !=root){
            Swap(virable_cost[small],virable_cost[root]);
            Heapify(virable_cost,size,small);  
        }
    }

    inline void Bulid_Virable_Cost_Heap(std::deque<Cost> &virable_cost,int size){
        for(int i = size/2-1;i>=0;i--){
            Heapify(virable_cost,size,i);
        }
    }

    inline int Get_Min_Index(std::deque<Cost> &virable_cost){
        int size = virable_cost.size();
        if(size<=0) return -1;
        int real_index = virable_cost[0].real_index;
        virable_cost.pop_front();
        return real_index;
    }

    inline void Sort_Min_Edge(){
        edge temp;
        for(int i = 0;i <arcnum-1; i++){
            for(int j = 0; j<arcnum-1-i; j++){
                if(Edge[j].lowcost>Edge[j+1].lowcost){
                    temp = Edge[j];
                    Edge[j] = Edge[j+1];
                    Edge[j+1] = temp;
                }
            }
        }
    }

    inline int Select_Min(std::vector<Cost>&cost)const{
        int index;
        for(int i = 0; i<vexnum; i++){
            if(cost[i].lowcost!=0){
                index = i;
                break;
            }
        }
        for(int j = 0; j<vexnum; j++){
            if(cost[j].lowcost!=0 && cost[j].lowcost < cost[index].lowcost){
                index = j;
            }
        }
        return index;
    }
    
    inline int Locate_Vex(char vex){
        for(int i = 0; i<vexnum;i++){
            if(MG.vexs[i].vex_name == vex) return i;
        }
        return -1;
    }

    inline void Inital_Mat_Graph(){
        MG.arcs.resize(vexnum, std::vector<int>(vexnum,MVINT));
    }

    inline void Display_Mat_Graph(){
        std::cout<<"1.Display Mat_Graph"<<std::endl;
        for(int i = 0; i<vexnum;i++){
            std::cout<<MG.vexs[i].vex_name<<" ";
        }
        std::cout<<std::endl;

        for(int i = 0; i<vexnum; i++){
            for(int j = 0; j<vexnum; j++){
                std::cout<<MG.arcs[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    inline void Read_File_Generate_Mat(){
        std::ifstream file("E:\\HomeWork\\lab3\\GRAPH.txt");
        if(!file.is_open()){
            std::cout<<"Fail to open the GRAPH.txt";
            return ;
        }
        std::string line;
        if(std::getline(file,line)){
            std::stringstream ss(line);
            char vertex;
            while(ss>>vertex){
                MG.vexs.push_back({vertex,false,false});
            }
        }
        std::string edge;
        int weight;
        while(file>>edge>>weight){
            char v1 = edge[0];
            char v2 = edge[1];

            int pos1 = Locate_Vex(v1);
            int pos2 = Locate_Vex(v2);

            if(pos1!=-1 && pos2!=-1){
                MG.arcs[pos1][pos2] = weight ;
                MG.arcs[pos2][pos1] = weight ;
            }
        }
        file.close();
    }

};

int main(void)
{
    Mat_Graph_Operator MG(10,19);
    MG.Mat_Graph_Control();
    return 0;
}

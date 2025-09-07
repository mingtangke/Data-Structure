#include "ulity.h"
constexpr int MVINT = 10000;
class Mat_Graph_Operator{
public:
    typedef struct{
        int vex_name;
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

    void Kruskal_Min_Span_Tree(bool apparent){
        if(apparent)std::cout<<"3.The Kruskal_Min_Span_Tree is :"<<std::endl;

        int sum_distance = 0;
        for(int i = 0; i<vexnum ;i++){
            MG.vexs[i].connected = i;
        }
        for(int i = 0; i<vexnum; i++){
            for(int j = 0; j<=i; j++){
                 if(MG.arcs[i][j] != MVINT){
                        Edge.push_back({i,j,MG.arcs[i][j]});
                    }
            }
        }

        Sort_Min_Edge();

        // for(int i = 0;i<arcnum;i++){
        //     std::cout<<Edge[i].lowcost<<" ";
        // }
        // std::cout<<std::endl;
        int valid = 0;
        for(int i = 0; i<arcnum; i++){
            
            int v1 = Edge[i].front_index;
            int v2 = Edge[i].rear_index;
            int vs1 = MG.vexs[v1].connected;
            int vs2 = MG.vexs[v2].connected;
            
            if(vs1!=vs2){
            sum_distance += Edge[i].lowcost;
            if(apparent){
            std::cout<<MG.vexs[v1].vex_name<<"<->"<<MG.vexs[v2].vex_name<<" "<<Edge[i].lowcost<<std::endl;
            }
            MG.vexs[v2].connected = vs1; 
            valid ++;
            if(valid == vexnum-1){
                //break;
            }
            for(int j = 0; j<vexnum; j++){
                if(MG.vexs[j].connected == vs2) MG.vexs[j].connected = vs1;
                }  
            }
        }
        if(apparent)std::cout<<"Kruskal_The total distance is :"<<sum_distance<<std::endl;
    }


    
    void Prime_Min_Span_Tree(bool apparent){
        if(apparent){
        std::cout<<"1.The Prime_Min_Span_Tree is :"<<std::endl;
        }
        int sum_distance = 0;
        cost.resize(vexnum);

        int center = 0;
        for(int i = 0; i<vexnum; i++){
            cost[i].adjvex_index = center;
            cost[i].real_index = i;
            cost[i].lowcost = center!=i ? MG.arcs[center][i]:0;
        }
        for(int k = 0; k<vexnum-1; k++){
            int next_index = Select_Min(cost);
            sum_distance += MG.arcs[next_index][cost[next_index].adjvex_index];
            if(apparent){
            std::cout<<MG.vexs[next_index].vex_name<<"<->"<<MG.vexs[cost[next_index].adjvex_index].vex_name<<" "
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
        if(apparent){
            std::cout<<"Prime_The total distance is :"<<sum_distance<<std::endl;
            std::cout<<std::endl;
        }
    }

    void Measure_Heapify_1_Prime_Min_Span_Tree() {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i< 10*MVINT;i++) Heapify_1_Prime_Min_Span_Tree(false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Heapify_1_Prime_Min_Span_Tree took " << duration.count() << " seconds.\n";
    }
    void Measure_Heapify_2_Prime_Min_Span_Tree() {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i< 10*MVINT;i++) Heapify_2_Prime_Min_Span_Tree(false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Heapify_2_Prime_Min_Span_Tree took " << duration.count() << " seconds.\n";
    }

    void Measure_Prime_Min_Span_Tree() {
        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i< 10*MVINT;i++) Prime_Min_Span_Tree(false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Prime_Min_Span_Tree took " << duration.count() << " seconds.\n";
    }

    void Measure_Kruskal_Min_Span_Tree(){
        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i< 10*MVINT;i++) Kruskal_Min_Span_Tree(false);
 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Kruskal_Min_Span_Tree: took " << duration.count() << " seconds.\n";
    }

    virtual void Mat_Graph_Control(){
        //Display_Mat_Graph();
        //Prime_Min_Span_Tree(true);
        //Heapify_1_Prime_Min_Span_Tree(true);
        //Heapify_2_Prime_Min_Span_Tree(true);
        //Kruskal_Min_Span_Tree(true);
        std::cout<<"The runtime of 10000 times"<<std::endl;
        std::cout<<"1.Naive Prime:"<<std::endl;
        Measure_Prime_Min_Span_Tree();
        //std::cout<<"2.Static Heapify Prime,the constant num is the large:"<<std::endl;
        Measure_Heapify_1_Prime_Min_Span_Tree();
        std::cout<<"3.Dynamic Heapify Prime,the final version:"<<std::endl;
        //Measure_Heapify_2_Prime_Min_Span_Tree();
        std::cout<<"4.Kruskal_Min_Span_Tree:"<<std::endl;
        //Measure_Kruskal_Min_Span_Tree();
    }

void Heapify_1_Prime_Min_Span_Tree(bool apparent){
        if(apparent){
        std::cout<<"2.The Heapify_1_Prime_Min_Span_Tree is :"<<std::endl;
        }
        //std::cout<<MG.vexs[0].vex_name<<" ";
        std::vector<Cost>cost;
        int sum_distance = 0;
        int center = 0;
        cost.resize(vexnum);
        for(int i = 0; i<vexnum; i++){
            cost[i].adjvex_index = center;
            cost[i].real_index = i;
            cost[i].lowcost = center!=i ? MG.arcs[center][i]:0;
        }
        for(int k = 0; k<vexnum-1; k++){
            int next_index = Get_Min_Index_1(cost,cost.size());
            sum_distance += MG.arcs[next_index][cost[next_index].adjvex_index];
            if(apparent){
            std::cout<<MG.vexs[next_index].vex_name<<"<->"<<MG.vexs[cost[next_index].adjvex_index].vex_name<<" "
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
       if(apparent){
            std::cout<<"Prime_The total distance is :"<<sum_distance<<std::endl;
            std::cout<<std::endl;
        }
    }

   inline void Print(std::deque<Cost> &virable_cost){
        for(int i = 0;i<virable_cost.size();i++){
            std::cout<<virable_cost[i].lowcost<<" "<<virable_cost[i].real_index+1<<std::endl;
        }
        std::cout<<"---------------------------------"<<std::endl;
   }

    void Insert(std::deque<Cost> &virable_cost,Cost value){
        virable_cost.push_back(value);
        Heapify_Float_Up_2(virable_cost,virable_cost.size()-1);
    }

    void Heapify_2_Prime_Min_Span_Tree(bool apparent){
        if(apparent){
        std::cout<<"3.The Heapify_2_Prime_Min_Span_Tree is :"<<std::endl;
        }
        std::deque<Mat_Graph_Operator::Cost>virable_cost;
        std::vector<Mat_Graph_Operator::Cost>const_cost(vexnum);

        int center = 0,sum_distance = 0,existed_vex_num = 0;

        for(int i = 0; i<vexnum; i++){
            const_cost[i].adjvex_index = center;
            const_cost[i].real_index = i;
            const_cost[i].lowcost = MVINT;
        }

        Insert(virable_cost,const_cost[0]);
        //MG.vexs[0].visited = true;

        while(!virable_cost.empty()){
            if(existed_vex_num == vexnum) break;
            int min_index = Get_Min_Index_2(virable_cost);
            if(MG.vexs[min_index].visited) continue;

            existed_vex_num++;
            MG.vexs[min_index].visited = true;

            if(apparent && min_index != const_cost[min_index].adjvex_index){
            	sum_distance += MG.arcs[min_index][const_cost[min_index].adjvex_index];
                std::cout<<MG.vexs[min_index].vex_name<<"<->"<<MG.vexs[const_cost[min_index].adjvex_index].vex_name<<" "
             <<MG.arcs[min_index][const_cost[min_index].adjvex_index]<<std::endl;
            }

            for(int i = 0; i <vexnum;i++){
                if(!MG.vexs[i].visited && const_cost[i].lowcost > MG.arcs[min_index][i]){
                    const_cost[i].adjvex_index = min_index;
                    const_cost[i].lowcost = MG.arcs[min_index][i];
                    Insert(virable_cost,const_cost[i]);
                }
            }
        }

        if(apparent) {
            std::cout<<"The total distance is :"<<sum_distance<<std::endl;
            std::cout<<std::endl;
        }
    }
protected: 
//----------------------------------下面是Heapify_1的辅助函数-------------------------------------//  
    inline void Heapify(std::vector<Cost> &cost,int size,int root){
        int small = root;
        int lchild = root*2+1;
        int rchild = root*2+2;
        if(lchild < size && cost[small].lowcost>cost[lchild].lowcost){
            small = lchild;
        } 
        if(rchild < size && cost[small].lowcost>cost[rchild].lowcost){
            small = rchild;
        }
        if(small !=root){
            Swap(cost[small],cost[root]);
            Heapify(cost,size,small);  
        }
    }

    inline void Bulid_Cost_Heap(std::vector<Cost>&cost,int size){
        for(int i = size/2-1;i>=0;i--){
            Heapify(cost,size,i);
        }
    }

    inline  int Get_Min_Index_1(std::vector<Cost> cost,int size){
        Bulid_Cost_Heap(cost,size);
        if(size<=0) return -1;
        if(size == 1){
            size--;
            return cost[0].real_index;
        }
        while(cost[0].lowcost == 0){
            cost[0] = cost[size-1];
            cost.pop_back();
            size--;
            Heapify(cost,size,0);
        }
        int index = cost[0].real_index;
        cost[0] = cost[size-1];
        cost.pop_back();
        size--;
        Heapify(cost,size,0);
        return index;
    }
    inline void Swap(Cost &cost1,Cost&cost2){
        Cost temp;
        temp = cost1;
        cost1 = cost2;
        cost2 = temp; 
    }
//------------------------------------上面是Heapify 1的辅助将函数，下面是Heapify_2的辅助函数------------------//
    inline void Heapify_Float_Up_2(std::deque<Cost> &virable_cost,int current){
 
        while(current > 0){
            int parent = (current-1)/2;
            if(virable_cost[parent].lowcost>virable_cost[current].lowcost){
                Swap(virable_cost[parent],virable_cost[current]);
                current = parent;
            }
            else{
                break;
            }
        }
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

    inline int Get_Min_Index_2(std::deque<Cost> &virable_cost){
        int size = virable_cost.size();
        if(size<=0) return -1;
        int real_index = virable_cost[0].real_index;
        Swap(virable_cost[0],virable_cost[virable_cost.size()-1]);
        virable_cost.pop_back();
        Heapify(virable_cost, virable_cost.size(), 0); 
        return real_index;
    }
//----------------------------------------other---------------------------------//  
    // inline int Locate_Vex(int vex_name){
  	// 		return vex_name-1;
    // }
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
        std::ifstream file("E:\\HomeWork\\lab3\\cleaned_edges.txt");
        if(!file.is_open()){
            std::cout<<"Fail to open the undirected_graph.txt";
            return ;
        }
        for(int i = 0;i<vexnum;i++){
            MG.vexs.push_back({i+1,false,false});
        }
    
        int edge1,edge2,weight;
        while(file>>edge1>>edge2>>weight){
                MG.arcs[edge1-1][edge2-1] = weight ;
                MG.arcs[edge2-1][edge1-1] = weight ;
        }
        file.close();
    }
};

int main(void)
{
    Mat_Graph_Operator MG(50,244);
    MG.Mat_Graph_Control();
    return 0;
}
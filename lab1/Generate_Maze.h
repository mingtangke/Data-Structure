#include "M_Stack.h"
#include <utility>
#include <vector>
#include <fstream>

constexpr int MVNUM = 50;

class Graze_Maze
{
public:
    typedef struct
    {
        std::pair<int, int> Position; 
        bool visited;                
        int label;                          
    } Vertix;

    int row, col;  // 将 row 和 col 放到 vexs 之前
    std::vector<Vertix> vexs;
    
    std::vector<std::vector<bool>> arcs;
    std::vector<std::vector<char>> Maze;
    //bool arcs[MVNUM][MVNUM];
    //char Maze[MVNUM][MVNUM];

    int vexnum;
    typedef struct 
    {
        std::pair<int, int> Position;
        int distance;
    }direction;
    std::vector<direction> Direction= {
        {{3,0},1},
        {{-3,0},-1},
        {{0,3},col},
        {{0,-3},-col},
        {{3,3},col+1},
        {{-3,-3},-col-1},
        {{3,-3},-col+1},
        {{-3,3},col-1}};

public:
    Graze_Maze(int _row, int _col): row(_row), col(_col), vexs(_col*_row+1)
    {
        arcs.resize(MVNUM, std::vector<bool>(MVNUM, false));
        Maze.resize(3 * row, std::vector<char>(3 * col, ' '));
        
        Inital_Maze();
    }
    ~Graze_Maze(){};

    void Inital_Maze()
    {
        vexnum = row * col;
        for (int i = 0; i <= vexnum; i++)
        {
            vexs[i].label = i;
            vexs[i].visited = false;
            vexs[i].Position.first = ((i-1) / col) * 3 + 1;
            vexs[i].Position.second = ((i-1) % col) * 3 + 1; 
        }

        for (int i = 1; i <= vexnum; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                i == j?arcs[i][j] = true : arcs[i][j] = false;
                arcs[j][i] = arcs[i][j];
            }
        }
    }
    
    void Random_Generate_Maze()
    {
        M_Stack<Vertix> S;
        vexs[1].visited = true;//下标从1开始
        S.Push(vexs[1]);
       
        while(!S.IsEmpty())
        {
            int count = 0;
            std::vector<int> record_nearby;//下标从0开始
            
            Vertix locate = S.Pop();
            for( std::vector<direction>::iterator it = Direction.begin();it!=Direction.end();it++)
            {
                int x = locate.Position.first + it->Position.first;
                int y = locate.Position.second + it->Position.second;
                int new_label = 0;

                if(Locate_Position(x,y,new_label)&&(!vexs[new_label].visited))
                {
                    count++;
                    if(count == 1) S.Push(locate);
                    record_nearby.push_back(new_label);
                }
            }
            
            if(count)
            {
                std::random_device rd;     
                std::mt19937 gen(rd()); // 使用 Mersenne Twister 生成器
                std::uniform_int_distribution<int> dist(0,record_nearby.size()-1); // 设定范围
                int random_label = record_nearby[dist(gen)];

                vexs[random_label].visited = true;
                arcs[locate.label][random_label] = true;
                arcs[random_label][locate.label] = true;

                S.Push(vexs[random_label]);
                
            }
        }
        Random_Generate_Disturbs();
        Visual_Maze();
        Save_Maze();
        std::cout<<"Yeah";
    }
    
    inline void Display_Arcs()
    {
        for(int i = 1;i <= vexnum; i++)
        {
            for(int j = 1;j <= i; j++)
            {
                if(arcs[i][j] == 1 && i!=j)
                std::cout<<i<<" "<<j<<std::endl;
            }
        }
    }

    inline bool Locate_Position(int x,int y,int &new_label)
    {
        for(int k = 1;k <= vexnum; k++){
         if(vexs[k].Position.first == x  && vexs[k].Position.second == y)
         {
            new_label = k;
            return true;
          }
        }
        return false;
    }

protected:
    inline void Display_Vex_Position()
    {
        for(int i=1;i<=vexnum;i++)
        {

                std::cout<<vexs[i].Position.first<<" "<<
                vexs[i].Position.second;
                std::cout<<vexs[i].label<<std::endl;
            }
    }
    
    bool Check_Is_All_Visited()
    {
        for(int i = 1;i <= vexnum ;i++)
        {
            if(!vexs[i].visited) return false;
        }
        return true;
    }
    
    void Random_Generate_Disturbs()
    {
        int upper = 2*sqrt(col*row),count = 0;
        while(count<upper)
        {
            std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
            std::uniform_int_distribution<int> distribution(1,vexnum-1);
            int i = distribution(generator);
            int j = i+1;
            if((!arcs[i][j]) && (i%col!=0) && (j%col!=0)) 
            {
                arcs[i][j] = true;
                count++;
            }
        }
    }

    inline void Display_Maze()
    {
        for(int i = 0;i < 3*row;i++)
        {
            for(int j = 0;j < 3*row;j++)
            {
                std::cout<<Maze[i][j];
            }
            std::cout<<std::endl;
        }   
    }

    void Visual_Maze()
    {
        for(int i = 0;i < 3*row; i++)
        {
            for(int j = 0;j < 3*col;j++)
            {
                int mod1 = i%3,mod2 = j%3;
                switch (mod1)
                {
                    case 0:
                    if(mod2 == 0) Maze[i][j] ='/';
                        else if(mod2 == 1) Maze[i][j] = '-'; 
                        else Maze[i][j] = '\\';
                        break;
                    case 1:
                        Maze[i][j] = '|';
                        break;
                    default:
                        if(mod2 == 0) Maze[i][j] ='\\';
                        else if(mod2 == 1) Maze[i][j] = '-';
                        else Maze[i][j] = '/';
                        break;
                }
            }
        }

        for(int k = 1;k <= vexnum; k++)
        {
            int x = vexs[k].Position.first;
            int y = vexs[k].Position.second;
            Maze[x][y] = '*';
        }

        std::cout<<std::endl;
        for(int i = 1;i <= vexnum; i++)
        {
            for(int j = 1;j <= vexnum; j++)
            {
                if(i!=j&&arcs[i][j]==1)
                {
                    int distance = abs(vexs[i].label-vexs[j].label);
                        
                    int x_i = vexs[i].Position.first;
                    int y_i = vexs[i].Position.second;
                    int x_j = vexs[j].Position.first;
                    int y_j = vexs[j].Position.second;

                    int min_x = x_i < x_j ? x_i : x_j;
                    int min_y = y_i < y_j ? y_i : y_j;
                    int max_y = y_i > y_j ? y_i : y_j;
                        
                    if(distance == 1){                        
                        Maze[min_x][min_y+1] = ' ';
                        Maze[min_x][min_y+2] = ' ';
                    }
                    else if(distance == col){
                        Maze[min_x+1][min_y] = ' ';
                        Maze[min_x+2][min_y] = ' ';
                    }
                    else if(distance == col+1){
                        Maze[min_x+1][min_y+1] = ' ';
                        Maze[min_x+2][min_y+2] = ' ';
                    }
                    else if(distance == col-1){
                        Maze[min_x+1][max_y-1] = ' ';
                        Maze[min_x+2][max_y-2] = ' ';
                    }
                    else{
                        throw std::runtime_error("The geneation of the maze failed");
                    }
                }
                   
            }
        }
        Display_Maze();
        std::cout<<std::endl;
    }

    void Save_Maze()
    {
        std::ofstream outFile("Maze.txt");
        if (!outFile)
        {
            std::cerr << "Fail to open the txt" << std::endl;
            return;
        }
        for (int i = 0; i < 3 * row; i++)
        {
            for (int j = 0; j < 3 * col; j++)
            {
                outFile << Maze[i][j];
            }
            if(i!=3*row-1) outFile << std::endl;
        }

        outFile.close();
        std::cout << "Succeed!" << std::endl;
    }

};




















































































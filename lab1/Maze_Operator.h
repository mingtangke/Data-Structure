#include "Generate_Maze.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>

class Maze_Operator:public Graze_Maze
{
public:
    std::vector<std::vector<char>> Received_Maze;

    Maze_Operator(int _row, int _col)
     : Graze_Maze(_row, _col),Received_Maze(3*_row, std::vector<char>(3*_col, '0')){
 
     }
    
    ~Maze_Operator(){};

    void Load_Maze()
    {
        std::ifstream inFile("Maze.txt");
        if (!inFile.is_open()) throw std::runtime_error("Failed to open txt");
        for (int i = 0; i < 3 * row; i++) 
        {
            for (int j = 0; j < 3 * col; j++)
            {
                Received_Maze[i][j] = inFile.get();
            }
            inFile.get();
        }

        inFile.close();
        std::cout << "Maze loaded successfully!" << std::endl;

        for(int i=0;i<3*row;i++)
        {
            for(int j=0;j<3*col;j++)
            {
                std::cout<<Received_Maze[i][j];
            }
            std::cout<<std::endl;
        }
    }

    void Stack_DFS_Only_Path()
    {
        int count_path = 0; 
        std::stack<int> S;
        //M_Stack<int> S;
        vexs[1].visited = true;
        S.push(1);
        while(!S.empty()&&!count_path)
        {
            int locate = S.top();
            S.pop(); 
            
            for( std::vector<direction>::iterator it = Direction.begin();it!=Direction.end();it++)
            {
            	bool jump_flag = false;
                int Ver_x,Ver_y,x_1,y_1,x_2,y_2,neighbor;
                Detect_Direction(locate,it,Ver_x,Ver_y,x_1,y_1,x_2,y_2);
                Locate_Position(Ver_x, Ver_y, neighbor);

                if(Received_Maze[x_1][y_1] == ' ' && Received_Maze[x_2][y_2] == ' '
                &&(!vexs[neighbor].visited))
                {
                    S.push(locate);
                    S.push(neighbor);
                    vexs[neighbor].visited = true;
                    jump_flag = true;
                }

                if(vexs[vexnum].visited) 
                {
                    Save_Stack_Only(S,"Stack_Only_Path.txt");

                    count_path++;
                    std::cout<<"Stack_Path:"<<count_path<<std::endl;
                    Stack_Display(S);
                    std::cout<<std::endl;
                }
                if(jump_flag) break;
            }
        }
    }
  
    void Recursion_DFS_All_Path()
    {
    	//M_Stack<int> record;
        //std::vector<M_Stack<int>> All_Paths;
        int time = 0;
        std::stack<int> record;
        std::vector<std::stack<int>> All_Paths;
        DFS(1,time,record,All_Paths);
        std::cout<<"The total paths are "<<time<<std::endl;
        Save_DFS_All_Paths(All_Paths);
    }

    void BFS_Shortest_Distance()
    {
        std::stack<int>Path;
        std::queue<int> Distance;
        std::vector<int>father;
        father.resize(100,0);
 
        int locate = 1;
        father[1] = 0;
        vexs[locate].visited = true;
        Distance.push(locate);

        while(!vexs[vexnum].visited && !Direction.empty())
        {
            locate = Distance.front();
            Distance.pop();
            for (std::vector<direction>::iterator it = Direction.begin(); it != Direction.end(); it++)
            {
                int Ver_x,Ver_y,x_1,y_1,x_2,y_2,neighbor;
                Detect_Direction(locate,it,Ver_x,Ver_y,x_1,y_1,x_2,y_2);
                Locate_Position(Ver_x, Ver_y, neighbor);
                if (Received_Maze[x_1][y_1] == ' ' && Received_Maze[x_2][y_2] == ' ' && !vexs[neighbor].visited)
                {
                    Distance.push(neighbor);
                    //std::cout<<neighbor<<" " ;
                    vexs[neighbor].visited = true;
                    father[neighbor] = locate;
                }
            }
        }
        if(vexs[vexnum].visited)
        {    	
            int son = vexnum,dad = father[son];

            while(dad)
            {
                dad = father[son];
                Path.push(son);
                son = dad;
            }

            Save_Shortest_Path(Path,"Shortest_Path.txt");

            std::cout<<"The shortest path is:";
            while(!Path.empty())
			{
				std::cout<<Path.top()<<" ";
				Path.pop();	
			}            
            std::cout<<std::endl;
        }
        else std::cout<<"No path"<<std::endl;
    }

protected:

    void Detect_Direction(int locate,std::vector<direction>::iterator it,
    int &Ver_x,int &Ver_y,int &x_1,int &y_1,int &x_2,int &y_2)
    {
        Ver_x = vexs[locate].Position.first + it->Position.first;
        Ver_y = vexs[locate].Position.second + it->Position.second;

        x_1 = vexs[locate].Position.first + it->Position.first / 3;
        y_1 = vexs[locate].Position.second + it->Position.second / 3;

        x_2 = vexs[locate].Position.first + 2 * it->Position.first / 3;
        y_2 = vexs[locate].Position.second + 2 * it->Position.second / 3;
    }

    void DFS(int locate, int &time,std::stack<int>& record, std::vector<std::stack<int>>& All_Paths)
    {
        vexs[locate].visited = true;
        record.push(locate);
        //std::cout<<"Entering node"<<<locate<<std::endl;

        if (locate == vexnum)
        {
            time++;
            std::cout<<"The path"<<time<<":";
            Stack_Display(record);
            All_Paths.push_back(record);
            record.pop();
            vexs[locate].visited = false;
            //std::cout<<"Exiting1"<<locate<<"Found"<< std::endl;
            return;
        }

        for (std::vector<direction>::iterator it = Direction.begin(); it != Direction.end(); it++)
        {
            int Ver_x,Ver_y,x_1,y_1,x_2,y_2,neighbor;
            Detect_Direction(locate,it,Ver_x,Ver_y,x_1,y_1,x_2,y_2);
            Locate_Position(Ver_x, Ver_y, neighbor);
            if (Received_Maze[x_1][y_1] == ' ' && Received_Maze[x_2][y_2] == ' ' && !vexs[neighbor].visited)
            {
                DFS(neighbor,time,record,All_Paths);
                //if(neighbor!=vexnum) record.pop();这个pop和下面那个任选都行()....
            }
        }
    
        record.pop();
        vexs[locate].visited = false;
        //std::cout<<"Exiting2<<locate<<std::endl;
    }

    void Stack_Display(std::stack<int> &record)
    {
            std::stack<int> copy = record,temp;
            std::vector<int> out_put;
            while(!copy.empty())
            {
                temp.push(copy.top());
                copy.pop();
            }
            while(!temp.empty())
            {
                out_put.push_back(temp.top());
                temp.pop();
            }
            for(std::vector<int>::iterator it = out_put.begin();it!= out_put.end();it++)
            {
                std::cout<<*it<<" ";
            }
            std::cout<<std::endl;
    }

    void Save_Stack_Only(std::stack<int> S,std::string location)
    {
        
        std::ofstream outFile(location);
        if (!outFile)
        {
            std::cerr << "Fail to open the txt" << std::endl;
            return;
        }
        std::vector<int> temp;

        while (!S.empty()) {
            temp.push_back(S.top());
            S.pop();
        }

        std::reverse(temp.begin(), temp.end());

        for (std::vector<int>::iterator it=temp.begin();it!=temp.end();it++)
         {
            outFile << *it << " ";
        }

        outFile.close();
    }
    
    void Save_DFS_All_Paths(std::vector<std::stack<int>> All_Paths)
    {
        
        std::ofstream outFile("All_Path.txt");
        if (!outFile)
        {
            std::cerr << "Fail to open the txt" << std::endl;
            return;
        }
        int time = 0;
        
        for (std::vector<std::stack<int>>::iterator it = All_Paths.begin(); it != All_Paths.end(); it++)
        {
            time++;
            outFile << "Path " << time << ": ";
            std::vector<int> temp;

            while (!(*it).empty()) 
            {
                temp.push_back((*it).top());
                (*it).pop();
            }

            std::reverse(temp.begin(), temp.end());
            for (auto it_ = temp.begin();it_!=temp.end();it_++)//类型不匹配，用auto 
            {
                outFile<<*it_;
                if (it_!=temp.end()-1) outFile << " -> ";
            }
             outFile << std::endl;
        }

        outFile.close();
        std::cout << "Saved Succeed!" << std::endl;
    }

    void Save_Shortest_Path(std::stack<int> S,std::string location)
    {
        std::ofstream outFile(location);
        if (!outFile)
        {
            std::cerr << "Fail to open the txt" << std::endl;
            return;
        }
        std::vector<int> temp;
        while (!S.empty()) {
            temp.push_back(S.top());
            S.pop();
        }
        for (std::vector<int>::iterator it=temp.begin();it!=temp.end();it++)
        {
            outFile << *it << " ";
        }
        outFile.close();
    }
};










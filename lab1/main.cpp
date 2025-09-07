#include "Maze_Operator.h"
#include <iostream>
int main(void)
{
    std::cout<<"You can generate the maze Randomly,or directly use the maze_1.txt"<<std::endl;
    std::cout<<"1.generate the maze Randomly  2.use the maze_1.txt"<<std::endl;
    int ch,row,col;
    std::cin>>ch;
    if(ch==1)
    {
        std::cout<<"Input row and col,both<=6"<<std::endl;
        std::cin>>row>>col;
        Graze_Maze maze(row,col);
        std::cout<<"---Slow------Slow---Slow-----Slow--------"<<std::endl;
        maze.Random_Generate_Maze();
    }
    else
    {
        row = 6;
        col = 6;
    }
    Maze_Operator M1(row,col);
    M1.Load_Maze();

    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"1.Only one path ? 2.Show all paths and the shortest one"<<std::endl;
    
    std::cin>>ch;
    if(ch==1)
    {
        std::cout<<"----------------------------------------"<<std::endl;
        M1.Stack_DFS_Only_Path();
        std::cout<<"----------------------------------------"<<std::endl;
    }
    else
    {  
        std::cout<<"----------------------------------------"<<std::endl;
        M1.Recursion_DFS_All_Path();
        std::cout<<"----------------------------------------"<<std::endl;
        M1.BFS_Shortest_Distance();
        std::cout<<"----------------------------------------"<<std::endl;
    }
    
    return 0;
}











































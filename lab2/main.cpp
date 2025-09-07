#include "K_Ray_Huffman.h"
#include "Pieces_Huffman.h"
#include <iostream>

int main(void){
    int K = 5;
    Huffman_Operator Binary_Operator;
    Pieces_Huffman_Operator Blanket_Binary_Operator;
    K_Ray_Huffman_Operator K_Ray_Operator(K);
    std::cout<<"----------------------Binary Huffman Tree----------------------------------"<<std::endl;
    Binary_Operator.Generate_Huffman_Code();
    std::cout<<"----------------------Blanket Binary Huffman Tree-------------------------"<<std::endl;
    Blanket_Binary_Operator.Generate_Huffman_Code();
    std::cout<<"----------------------K_Ray Huffman Tree-----------------------------------"<<std::endl;
    K_Ray_Operator.Generate_Huffman_Code();
    return 0;
}
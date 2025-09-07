#include <iostream>
#include <vector>
#include <stdexcept>
#include "K_HTNode.h"

// typedef struct K_HTNode{
//         int real_pos;
//         int weight;
//         std::vector<int> relation;
// }K_HTNode;

void Swap(K_HTNode &a,K_HTNode &b) {
    K_HTNode temp = a;
    a = b;
    b = temp;
}

void heapify(std::vector<K_HTNode> &heap,int root) {
    int size = heap.size();
    int small = root;
    int lchild = root * 2 + 1;
    int rchild = root * 2 + 2;

    if (lchild < size && heap[small].weight > heap[lchild].weight) {
        small = lchild;
    }
    if (rchild < size && heap[small].weight > heap[rchild].weight) {
        small = rchild;
    }
    if (root != small) {
        Swap(heap[small], heap[root]);
        heapify(heap, small);
    }
}

void Float_Top(std::vector<K_HTNode> &heap, int current) {
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap[current].weight < heap[parent].weight) {
            Swap(heap[current], heap[parent]);
            current = parent;
        }else{
            break;
        }
    }
}

void Build_Heap(std::vector<K_HTNode> &heap) {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapify(heap, i);
    }
}

int Get_Min(std::vector<K_HTNode> &heap,int &sum) {
    int size = heap.size();
    if (size <= 0) {
        throw std::logic_error("Heap is empty!");
    }
    if (size == 1) {
        heap.pop_back();
        return heap[0].real_pos;
    }
    sum += heap[0].weight;
    int root = heap[0].real_pos;
    heap[0] = heap[size - 1];
    heap.pop_back();
    heapify(heap,0);
    return root;
}

void printHeap(const std::vector<K_HTNode>&heap) {
    //std::cout<<heap.size();
    for (size_t i = 0; i < heap.size(); i++) {
        std::cout << heap[i].weight << " ";
    }
    std::cout << std::endl;
}

void Get_K_Min(std::vector<K_HTNode>heap, std::vector<std::vector<int>> &result, int k) {
    for(size_t i=0;i<heap.size()-1;i++){
        heap[i] = heap[i+1];
    }
    heap.pop_back();//actually pop the front
    
    size_t constant = heap.size() + 1;
    Build_Heap(heap);
    //std::cout<<"Inital heap"<<std::endl;
    //printHeap(heap);

    while (heap.size() >= k) {
        int sum = 0;
        K_HTNode add;
        std::vector<int>temp;
        for (int i = 0; i < k; i++) {
            //printHeap(heap);
            int real_pos = Get_Min(heap,sum);
            temp.push_back(real_pos);
            //std::cout << min << " ";
        }
        add.weight = sum;
        add.real_pos = constant;
        constant++;
        heap.push_back(add);
        result.push_back(temp);
        Float_Top(heap, heap.size() - 1);
        temp.clear();
    }
    if(heap.size() != 1) throw std::logic_error("heap.size()");

}

/*int main() {
    std::vector<K_HTNode>A;
    std::vector<std::vector<int>> result;
    int K = 3;
    for(int i = 0; i<=10;i++){
        K_HTNode node;
        node.real_pos = i;
        node.weight = i;
        A.push_back(node);
    }
    Get_K_Min(A, result, K);
    for(int i = 0;i<result.size();i++){
        for(int j = 0;j<K;j++){
            std::cout<<result[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    // for(int i=0;i<A.size();i++){
    //     std::cout<<A[i].weight<<std::endl;//check bug
    // }
    return 0;
}*/



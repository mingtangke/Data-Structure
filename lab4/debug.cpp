#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <queue>

void Display(std::vector<int>&array){
	for(int m = 0;m<array.size();m++) std::cout<<array[m]<<" ";
	std::cout<<std::endl;
}
void Heapfy(std::vector<int>&array,int root,int end){
	int left = 2*root + 1;
	int right = 2*root +2;
	int current = root;
	if(array[left]>array[current] && left < end){
		current = left;
	}
	if(array[right]>array[current] && right < end){
		current = right;
	}
	if(root!=current){
		std::swap(array[current],array[root]);
		Heapfy(array,current,end);
	}
}

void HeapSort(std::vector<int>array){
	int size = array.size();
	int start = (size-2)/2;
	for(int i = start ;i >= 0; i--){
		Heapfy(array,i,size);
	}
		Display(array);
	for(int k = size-1; k>0; k--){
		std::swap(array[k],array[0]);
		Heapfy(array,0,k);
		Display(array);
	}
  	
}


int main(void){
    std::vector<int>array = {5,1,1,2,0,0};
    HeapSort(array);
    return 0;
}

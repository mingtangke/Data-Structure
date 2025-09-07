#include "utils.h"
#include "Link_Queue.h"

class Sort_Methods{
public:
std::vector<int> array;
    Sort_Methods(){
        // Read_Data_From_txt("E:\\HomeWork\\lab4\\output\\Data1.txt",array);
    }

    void Generate_Random_Data(const std::string& filename, int n = 999999, int lower_bound = -99999, int upper_bound = 99999) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open "<<filename<< std::endl;
            return;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(lower_bound, upper_bound);

        file<<n<<" ";
        for (int i = 0; i < n; ++i) {
            file<<dist(gen);
            if (i != n - 1) file<<" ";
        }
    file.close();
    }
  void Controller() {

        Merge(array);
        Save_To_File("Merge_Sort_Result.txt", array);

        QuickSort(array);
        Save_To_File("QuickSort_Result.txt", array);

        Direct_Select_Sort(array);
        Save_To_File("Direct_Select_Sort_Result.txt", array);

        HeapSort(array);
        Save_To_File("HeapSort_Result.txt", array);

        Radix_Sort(array, 5);  
        Save_To_File("Radix_Sort_Result.txt", array);

        Merge_Reverse(array);
        Save_To_File("Merge_Reverse_Result.txt", array);
    }

   
    
    void Read_Data_From_txt(std::string addrress,std::vector<int>&array) {
        std::ifstream file(addrress);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open input.txt" << std::endl;
            return;
        }
        int n;
        file >> n;
        array.resize(n);
        for (int i = 0; i < n; ++i) {
            file >> array[i];
        }
        file.close();
        std::cout << "Data read from input.txt. Size: " << n << std::endl;
//		  Show_Array(array);
    }


void Test_Running_Time() {
        // Read_Data_From_txt("output/Data5.txt");
        std::ofstream time_file("All_Algorithm_Running_Times.csv");
        time_file << "Algorithm,TotalTime us" << std::endl;
        std::vector<std::string>Data = {"E:\\HomeWork\\lab4\\output\\Data5.txt",
                                        "E:\\HomeWork\\lab4\\output\\Data4.txt",
                                        "E:\\HomeWork\\lab4\\output\\Data3.txt",
                                        "E:\\HomeWork\\lab4\\output\\Data2.txt",
                                        "E:\\HomeWork\\lab4\\output\\Data1.txt"};
    
    // for(int k = 01 ;k<= 5;k++){
        std::vector<int>temp;
        // Read_Data_From_txt(Data[k-1],temp);
        Read_Data_From_txt(Data[4],temp);
        // time_file<<(k*10+1)*9<<" ";
        long long mergeTotalTime = 0;
        long long quickTotalTime = 0;
        long long directSelectTotalTime = 0;
        long long heapTotalTime = 0;
        long long radixTotalTime = 0;
        
        std::vector<int> copy = temp;
        // auto start1 = std::chrono::high_resolution_clock::now();
        // for (size_t i = 0; i < 1000; i++) {
        //     copy = temp;
        //     Merge(copy);
        // }
        // auto end1 = std::chrono::high_resolution_clock::now();
        // mergeTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();
        
        // auto start2 = std::chrono::high_resolution_clock::now();
        // for (size_t i = 0; i < 1000; ++i) {
        //     copy = temp;
        //     QuickSort(copy);
        // }
        // auto end2 = std::chrono::high_resolution_clock::now();
        // quickTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

        // auto start3 = std::chrono::high_resolution_clock::now();
        // for (size_t i = 0; i < 1000; ++i) {
        //     copy = temp;
        //     Direct_Select_Sort(copy);
        // }
        // auto end3 = std::chrono::high_resolution_clock::now();
        // directSelectTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count();

        // auto start4 = std::chrono::high_resolution_clock::now();
        // for (size_t i = 0; i < 1000; ++i) {
        //     copy = temp;
        //     HeapSort(copy);
        // }
        // auto end4 = std::chrono::high_resolution_clock::now();
        // heapTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4).count();

        auto start5 = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < 1000; ++i) {
            copy = temp;
            Radix_Sort(copy,5);
        }
        auto end5 = std::chrono::high_resolution_clock::now();
        radixTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(end5 - start5).count();
        std::cout<<radixTotalTime<<std::endl;

        // time_file << "Merge Sort," << mergeTotalTime << std::endl;
        // time_file << "QuickSort," << quickTotalTime << std::endl;
        // time_file << "Direct Select Sort," << directSelectTotalTime << std::endl;
        // time_file << "HeapSort," << heapTotalTime << std::endl;
        // time_file << "Radix Sort," << radixTotalTime << std::endl;
    // }
    // time_file.close();
    // std::cout << "Algorithm running times have been saved to Algorithm_Running_Times.csv" << std::endl;
}

void Save_To_File(const std::string& filename, const std::vector<int>& array) {
    std::ofstream file(filename);
    if (!file.is_open()){
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }
    for (int num : array) {
        file << num << " ";
    }
    file.close();
    std::cout << "Saved result to file: " << filename << std::endl;
}


void HeapSort(std::vector<int>array){
	int size = array.size();
	int start = (size-2)/2;
	for(int i = start ;i >= 0; i--){
		Heapfy(array,i,size);
	}
	for(int k = size-1; k>0; k--){
		std::swap(array[k],array[0]);
		Heapfy(array,0,k);
	}
	// for(int m = 0;m<size;m++) std::cout<<array[m]<<" ";
  
}


void QuickSort(std::vector<int> array){
    Quick(array,0,array.size()-1);
    // Show_Array(array);
}

void Direct_Select_Sort(std::vector<int> array){
    for(int i = 0; i < array.size(); i++){
        int min_index = i;
        for(int j = min_index; j < array.size(); j++){
            if(array[min_index] > array[j]){
                min_index = j;
            }
        }
        if(i != min_index);
        std::swap(array[min_index],array[i]);
    }    
    // Show_Array(array);
}
void Merge(std::vector<int>array){
    std::vector<int>temp(array.size());
    // std::memset(&temp,0,temp.size());
    Merge_Sort(0,array.size()-1,array,temp);
    // Show_Array(array);
}

void Merge_Reverse(std::vector<int> array){
    std::vector<int>temp(array.size());
    long long count = Merge_Count(0,array.size()-1,array,temp);
    // Show_Array(array);
    // std::cout<<"The total num of the reverse :"<<count<<std::endl;
}

void Radix_Sort(std::vector<int>array,int figure){
     std::vector<int> positives, negatives;

    for (int num : array) {
        if (num >= 0)
            positives.push_back(num);
        else
            negatives.push_back(-num); 
    }

    if (!positives.empty())
        // Radix_Sort_Update(positives,figure);
        Radix_Sort_Naive(positives,figure);

    if (!negatives.empty()) {
        // Radix_Sort_Update(negatives,figure);
        Radix_Sort_Naive(positives,figure);
        for (int& num : negatives)
            num = -num; // 恢复为负数
        reverse(negatives.begin(), negatives.end()); // 翻转顺序
    }

    array.clear();
    array.insert(array.end(), negatives.begin(), negatives.end());
    array.insert(array.end(), positives.begin(), positives.end());
    // Show_Array(array);
}

private:

inline int Caculate_Figure(int k,int p){
    int power = 1;
    for(int i = 1;i < p;i++){
        power *= 10;
    }
    return (k%(power*10))/power;
}


inline void Heapfy(std::vector<int>&array,int root,int end){
	int left = 2*root + 1;
	int right = 2*root +2;
	int current = root;
	if(left < end && array[left]>array[current]){
		current = left;
	}
	if(right < end && array[right]>array[current] ){
		current = right;
	}
	if(root!=current){
		std::swap(array[current],array[root]);
		Heapfy(array,current,end);
	}
}

inline void Quick(std::vector<int> &array,int begin,int end){
   //no while here,since begin and end is actuall a constant,
   //the function cannot be popped out of the stack; 
   if(begin < end){
        int key = array[end];
        int i = begin - 1;
        for(int  j= begin; j<end; j++){
            if(array[j] < key ){ 
                i++;
                std::swap(array[i],array[j]);
            }
        }
        std::swap(array[i+1],array[end]);
        int next_pos = i + 1;
        Quick(array,begin,next_pos-1);
        Quick(array,next_pos+1,end);
    }
}

inline int Merge_Sort(int l,int r,std::vector<int> &array,std::vector<int> &temp){
    int mid = (l + r)/2;
    if(l < r){
        Merge_Sort(l,mid,array,temp);
        Merge_Sort(mid+1,r,array,temp);
        Merge_Two(l,mid,r,array,temp);

    }
}

inline void Merge_Two(int l,int m,int r,std::vector<int>&array,std::vector<int>&temp){
    int i = l, j = m+1, k = l;
    while(i <= m && j <= r){
        temp[k++] = array[i] <= array[j] ? array[i++]:array[j++];
    }
    while(i <= m) temp[k++] = array[i++];
    while(j <= r) temp[k++] = array[j++];

    for(int i = l; i <= r; i++){
        array[i] = temp[i];
    }
}


inline int Merge_Count(int l,int r,std::vector<int> &array,std::vector<int> &temp){
    int mid = (l + r)/2;
    long long count = 0;
    if(l < r){
        count += Merge_Count(l,mid,array,temp);
        count += Merge_Count(mid+1,r,array,temp);
        count += Merge_Two_Count(l,mid,r,array,temp);
        return count;
    }
    return 0;
}

inline int Merge_Two_Count(int l,int m,int r,std::vector<int>&array,std::vector<int>&temp){
    int i = l,j = m + 1,k = l;
    int count = 0;
    while(i <= m && j <= r){
        if(array[i] < array[j]){
            temp[k++] = array[i++];
        }else{
            count += (m - i + 1);
            temp[k++] = array[j++];
        }
    }
    while(i <= m) temp[k++] = array[i++];
    while(j <= r) temp[k++] = array[j++];
    for(int w = l; w <= r; w++){
        array[w] = temp[w];
    }
    return count;
}


inline void Show_Array(std::vector<int>& array){
    for(int num:array){
        std::cout<<num<<" ";
    }
    std::cout<<std::endl;
}

inline void Radix_Sort_Update(std::vector<int>&array,int figure){
    std::vector<Queue>QL(10);
    Queue temp;
    for(int num:array) temp.EnQueue(num);
    
    for(int pass = 1; pass <=figure; pass++){
        while (!temp.IsEmpty()){
            int data = temp.DeQueue();
            int r = Caculate_Figure(data,pass);
            QL[r].EnQueue(data);
        }
        temp.Clear();
        for(int k = 0;k <= 9; k++){
            while(!QL[k].IsEmpty()){
                temp.Concentrate(QL[k]);
            }
        }
    }
    for(size_t i = 0; i < array.size();i++) {
        // while(!temp.IsEmpty())  
        //bug covering old value
            array[i] = temp.DeQueue();
    }
    // std::cout<<"Radix_Sort"<<std::endl;
    // Show_Array(array);
}

 inline void Radix_Sort_Naive(std::vector<int>&array,int figure){
    std::vector<std::queue<int>>QL(10);
    for(int pass = 1; pass <=figure; pass++){
        for(int data:array){
            int r = Caculate_Figure(data,pass);
            QL[r].push(data);
        }
        array.clear();
        for(int k = 0;k <= 9; k++){
            while(!QL[k].empty()){
                array.push_back(QL[k].front());
                QL[k].pop();
            }
        }
        // Show_Array(array);
    }
    // std::cout<<"Radix_Sort"<<std::endl;
    // Show_Array(array);
    }

};


int main(void){
    Sort_Methods solution;
    // solution.Generate_Random_Data("Data5.txt");
    // solution.Controller();
    // solution.Test_Running_Time();
    solution.Test_Running_Time();
    
    return 0;
}
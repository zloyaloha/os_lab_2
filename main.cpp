#include "quicksort.h"

int main(){
    std::cout.setf(std::ios::fixed);
    std::vector<int>a;
    // std::vector<int>test{6,3,2,5,19,7,10,9};
    // QuickSort::ParallelQuickSort(test, 0, test.size() - 1, 4);
    // std::cout<<test;
    std::ifstream file ("../data/data.txt");
    if (!file) {
        perror("file isn't open");
    }
    std::string s;
    for(file >> s; !file.eof(); file >> s) 
        a.push_back(std::stoi(s));
    std::vector<int> b = a, c = a;
    
    clock_t start = clock();
    QuickSort::QuickSortStack(a, 0, a.size() - 1);
    clock_t end = clock();
    std::cout << "Time of working non recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    QuickSort::ParallelQuickSort(c, 0, c.size() - 1, 512);
    end = clock();
    std::cout << "Time of working parallel: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    QuickSort::QuickSortRecursive(b, 0, a.size() - 1);
    end = clock();
    std::cout << "Time of working recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}
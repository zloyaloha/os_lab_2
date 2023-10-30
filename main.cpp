#include "quicksort.h"

int main(){
    std::cout.setf(std::ios::fixed);
    std::ifstream file ("../data/data.txt");
    QuickSort arr(file);
    QuickSort b(arr), c(arr), d(arr);
    
    auto start = std::chrono::steady_clock::now();
    c.ParallelQuickSort(0, c.size() - 1, 9);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time of working parallel: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

//     start = std::chrono::steady_clock::now();
//     arr.QuickSortStack(0, arr.size() - 1);
//     end = std::chrono::steady_clock::now();
//     std::cout << "Time of working non recursive non parallel: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

//     start = std::chrono::steady_clock::now();
//     b.QuickSortRecursive(0, b.size() - 1);
//     end = std::chrono::steady_clock::now();
//     std::cout << "Time of working recursive non parallel: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

//     start = std::chrono::steady_clock::now();
//     d.ParallelQuickSortRecursive(0, d.size() - 1, 3);
//     end = std::chrono::steady_clock::now();
//     std::cout << "Time of working parallel recursive: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}
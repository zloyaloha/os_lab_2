#include "quicksort.h"

int main(){
    std::cout.setf(std::ios::fixed);
    std::vector<int>a;
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
    std::cout << "Time of working non recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    QuickSort::QuickSortRecursive(b, 0, a.size() - 1);
    end = clock();
    std::cout << "Time of working recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    QuickSort::ParallelQuickSort(c, 0, c.size() - 1, 2);
    end = clock();
    std::cout << "Time of working recursive parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
    // std::vector <int> nums{1,2,3,4,5,6,7};
    // auto iter = nums.cbegin();
    // nums.insert(iter + 4, iter, iter + 3);
    // nums.erase(nums.cbegin(), nums.cbegin() + 3);
    // auto iter = nums.cbegin();
    // nums.insert(iter + 4, iter, iter + 3);
    // nums.erase(nums.cbegin(), nums.cbegin() + 3);
    // std::cout << nums;
}
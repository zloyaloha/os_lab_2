#include "quicksort.h"

int main(int argc, char *argv[]){
    int threads;
    std::cout.setf(std::ios::fixed);
    std::ifstream file ("../data/data.txt");

    if (argc != 3) {
        return -1;
    } else {
        if (std::string(argv[1]) == "-f") {
            std::ifstream file ("../data/data.txt");
            std::ofstream fileTestOutput;
            fileTestOutput.open("../test.txt", std::ios::out);
            QuickSort arr(file);
            QuickSort a(arr), b(arr), c(arr), d(arr);
            int numOfThr = std::stoi(argv[2]);

            for (int i = 2; i < numOfThr; i++) {
                fileTestOutput<<i<<';';
                auto start = std::chrono::steady_clock::now();
                c.ParallelQuickSort(0, c.size() - 1, i);
                auto end = std::chrono::steady_clock::now();
                fileTestOutput<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<';';
        
                start = std::chrono::steady_clock::now();
                d.ParallelQuickSortRecursive(0, d.size() - 1, int(log2(i)));
                end = std::chrono::steady_clock::now();
                fileTestOutput<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<';';

                start = std::chrono::steady_clock::now();
                a.QuickSortRecursive(0, a.size() - 1);
                end = std::chrono::steady_clock::now();
                fileTestOutput<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<';';

                start = std::chrono::steady_clock::now();
                b.QuickSortStack(0, b.size() - 1);
                end = std::chrono::steady_clock::now();
                fileTestOutput<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<'\n';
                a = arr; b = arr; c = arr; d = arr;
            }
        } else if (std::string(argv[1]) == "-t") {
            std::ifstream file ("../data/data.txt");
            QuickSort arr(file);
            QuickSort a(arr), b(arr), c(arr), d(arr);
            int threads = std::atoi(argv[2]);

            auto start = std::chrono::steady_clock::now();
            c.ParallelQuickSort(0, c.size() - 1, threads);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Parallel QS time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "\n\n";
        
            start = std::chrono::steady_clock::now();
            d.ParallelQuickSortRecursive(0, d.size() - 1, int(log2(threads)));
            end = std::chrono::steady_clock::now();
            std::cout<< "Parallel QS Recursive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<" ms" << "\n\n";

            start = std::chrono::steady_clock::now();
            a.QuickSortRecursive(0, a.size() - 1);
            end = std::chrono::steady_clock::now();
            std::cout << "QS Recursive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<" ms" << "\n\n";

            start = std::chrono::steady_clock::now();
            b.QuickSortStack(0, b.size() - 1);
            end = std::chrono::steady_clock::now();
            std::cout<< "QS Stack time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << "\n\n";
        } else if (std::string(argv[1]) == "-o") {
            threads = std::stoi(argv[2]);
            std::cout << "Print array to sort\n";
            std::vector<int> arr;
            std::string tmp;
            while (true) {
                std::cin >> tmp;
                if (tmp == "!") break;
                arr.push_back(std::stoi(tmp));
            }
            QuickSort a(arr), b(arr);
            auto start = std::chrono::steady_clock::now();
            b.QuickSortStack(0, b.size() - 1);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Array: " << a << "Sorted array: " << b;
            std::cout << "QS Stack time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" <<"\n\n";
            b = a;

            start = std::chrono::steady_clock::now();
            b.QuickSortRecursive(0, b.size() - 1);
            end = std::chrono::steady_clock::now();
            std::cout << "Array: " << a << "Sorted array: " << b;
            std::cout << "QS Recursive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" <<"\n\n";
            b = a;

            start = std::chrono::steady_clock::now();
            b.ParallelQuickSortRecursive(0, b.size() - 1, int(log2(threads)));
            end = std::chrono::steady_clock::now();
            std::cout << "Array: " << a << "Sorted array: " << b;
            std::cout << "QS Parallel Recursive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" <<"\n\n";
            b = a;

            start = std::chrono::steady_clock::now();
            b.ParallelQuickSort(0, b.size() - 1, threads);
            end = std::chrono::steady_clock::now();
            std::cout << "Array: " << a << "Sorted array: " << b;
            std::cout << "QS Parallel Recursive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" <<"\n\n";
            b = a;
        } else {
            return -1;
        }
    }
}
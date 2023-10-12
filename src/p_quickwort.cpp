#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <ostream>
#include <iostream>
#include <stack>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <thread>

#define MAX_LEVEL 1000

typedef struct {
    std::vector<int> array;
    int l;
    int r;
}pthrdData;

std::ostream &operator << (std::ostream &os, const std::vector<int> a) {
    for (size_t i = 0; i < a.size(); ++i) {
        os << a[i] << ' ';
    }
    os << '\n';
    return os;
}
void swap(int &a, int&b) {
     int tmp = a;
     a = b;
     b = tmp;
}

std::pair<int,int> Partition(std::vector<int> &arr, int left, int right) {
    int medium = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < medium) {
            i++;
        }
        while (arr[j] > medium) {
            j--;
        }
        if (i <= j) {
            swap(arr[i++], arr[j--]);
        }
    }
    return std::make_pair(i, j);
}

void QuickSort(std::vector<int> &arr, int l, int r) {
    std::stack<std::pair<int, int>> s;
    std::pair <int, int> bord = std::make_pair(l, r), border;
    s.push(bord);
    while (!s.empty()) {
        bord = s.top();
        l = bord.first; r = bord.second;
        s.pop();
        if (bord.second <= bord.first) {
            continue;
        }
        border = Partition(arr, bord.first, bord.second);
        if (border.first < r) s.push(std::pair(border.first, r));
        if (border.first > l) s.push(std::pair(l, border.second));
    }
}

void QuickSortR(std::vector<int> &arr, int l, int r) {
    std::pair <int, int> border;
    border = Partition(arr, l, r);
    if (border.first < r) QuickSortR(arr, border.first, r);
    if (border.first > l) QuickSortR(arr, l, border.second);
}

void ParallelQuickSortR(std::vector<int> &arr, int l, int r, int level) {
    std::pair <int, int> border = Partition(arr, l, r);
    if (level < MAX_LEVEL) {
        if (border.first < r) {
            std::thread thr1(ParallelQuickSortR, std::ref(arr), border.first, r, level + 1);
            thr1.join();
        }
        if (border.first > l) {
            std::thread thr2(ParallelQuickSortR, std::ref(arr), l, border.second, level + 1);
            thr2.join();
        }
    } else {
        if (border.first < r) QuickSortR(arr, border.first, r);
        if (border.first > l) QuickSortR(arr, l, border.second);
    }
}

int main(){
    std::cout.setf(std::ios::fixed);
    std::vector<int> a;
    std::ifstream file ("../test/data.txt");
    if (!file) {
        perror("file isn't open");
    }
    std::string s;
    for(file >> s; !file.eof(); file >> s) 
        a.push_back(std::stoi(s));
    std::vector<int> b = a, c = a;
    clock_t start = clock();
    QuickSort(a, 0, a.size() - 1);
    clock_t end = clock();
    std::cout << "Time of working non recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    QuickSortR(a, 0, a.size() - 1);
    end = clock();
    std::cout << "Time of working recursive non parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
    start = clock();
    ParallelQuickSortR(c, 0, c.size() - 1, 0);
    end = clock();
    std::cout << "Time of working recursive parallel: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';
}
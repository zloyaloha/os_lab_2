#pragma once
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <ostream>
#include <iostream>
#include <queue>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <thread>
#include <cmath>
#include <mutex>
#include <atomic>
#include <condition_variable>
#define MAX_LEVEL 1000

class QuickSort {
    public:
        static void print(const std::vector<int> &a, int l, int r) ;
        static bool compare(const std::vector<int> &a, const std::vector<int> &b);
        static void swap(int &a, int&b);
        static std::pair<int,int> Partition(std::vector<int> &arr, const int &left, const int &right);
        static void QuickSortStack(std::vector<int> &arr, int l, int r);
        static void QuickSortRecursive(std::vector<int> &arr, int l, int r);
        static void ThreadFunc(std::vector<int> &arr, int num, std::vector<std::pair<int,int>> &borders);
        static void mergeArrays(std::vector<int> &arr, int l1, int mid, int r2);
        static void ParallelQuickSortRecursive(std::vector<int> &arr, int l, int r, int level);
        static void ParallelQuickSort(std::vector<int> &arr, int l, int r, int num);
    private:
        std::vector<int> _array;
};
std::ostream &operator << (std::ostream &os, const std::vector<int> a);
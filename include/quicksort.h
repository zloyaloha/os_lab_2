#pragma once
#include <stack>
#include <stdio.h>
#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <thread>
#include <cmath>
#include <chrono>

class QuickSort {
    public:
        friend std::ostream &operator << (std::ostream &os, const QuickSort &arr);
        int size();
        QuickSort(std::ifstream &file);
        QuickSort(const std::vector<int> &v);
        QuickSort(QuickSort &other);
        QuickSort(const std::initializer_list<int> &list);
        void print(int l, int r);
        bool operator == (const QuickSort &other) const;
        QuickSort& operator = (const QuickSort &other);
        std::pair<int,int> Partition(const int &left, const int &right);
        void QuickSortStack(int l, int r);
        void QuickSortRecursive(int l, int r);
        void ParallelQuickSortRecursive(int l, int r, int level);
        void ParallelQuickSort(int l, int r, int num);
    private:
        void mergeArrays(int l1, int mid, int r2);
        void swap(int &a, int&b);
        std::vector<int> _array;
};
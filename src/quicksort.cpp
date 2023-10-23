#include "quicksort.h"

std::ostream &operator << (std::ostream &os, const std::vector<int> a) {
    for (size_t i = 0; i < a.size(); ++i) {
        os << a[i] << ' ';
    }
    os << '\n';
    return os;
}

bool QuickSort::compare(const std::vector<int> &a, const std::vector<int> &b) {
    if (a.size() != b.size()) {
        return false;
    } else {
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) return false;
        }
    }
    return true;
}

void QuickSort::print(const std::vector<int> &a, int l, int r) {
    for (size_t i = l; i < r; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
} 

void QuickSort::swap(int &a, int&b) {
     int tmp = a;
     a = b;
     b = tmp;
}

std::pair<int,int> QuickSort::Partition(std::vector<int> &arr, const int &left, const int &right) {
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

void QuickSort::QuickSortRecursive(std::vector<int> &arr, int l, int r) {
    std::pair <int, int> border;
    border = Partition(arr, l, r);
    if (border.first < r) QuickSortRecursive(arr, border.first, r);
    if (border.first > l) QuickSortRecursive(arr, l, border.second);
}

std::mutex mutex;

void QuickSort::mergeArrays(std::vector<int> &arr, int left, int mid, int right) { 
    int i = 0, j = 0;
    // std::cout << 'i' << '\n';
    std::vector <int> res;
    while (left + i < mid && mid + j < right) { 
        if (arr[i + left] < arr[mid + j]) {
            res.push_back(arr[left + i]);
            i++;
            // std::cout<<res;
        } else {
            res.push_back(arr[mid + j]);
            j++;
            // std::cout<<res;
        }
    }
    while (i + left < mid) {
        res.push_back(arr[left + i]);
        i++;
        // std::cout<<res;
    }
    while (mid + j < right) {
        res.push_back(arr[mid + j]);
        j++;
        // std::cout<<res;
    }

    for (int it = 0; it < i + j; it++) {
        arr[left + it] = res[it];
    }
    // std::cout << res;
}


void QuickSort::ParallelQuickSort(std::vector<int> &arr, int l, int r, int num) {
    std::vector<std::thread> thsS;
    std::vector<std::thread> thsM;
    std::vector<std::pair<int, int>>ranges;
    for (int i = 0; i < num; ++i) {
        ranges.push_back(std::pair<int, int> {int(i * ceil(arr.size() / num)), int((i + 1) * ceil(arr.size() / num) - 1)});
        thsS.push_back(std::thread(QuickSortRecursive, std::ref(arr), int(i * ceil(arr.size() / num)), int((i + 1) * ceil(arr.size() / num) - 1)));
    }
    for (auto & th : thsS) th.join();
    while (ranges.size() > 1) {
        int n = ranges.size();
        for (int i = 0; i < n; i += 2) {
            thsM.push_back(std::thread(mergeArrays, std::ref(arr), ranges[i].first, ranges[i+1].first, ranges[i+1].second + 1));
            ranges.push_back(std::pair<int,int> {ranges[i].first, ranges[i+1].second});
        }
        for (auto & th1 : thsM) th1.join();
        thsM.clear();
        ranges.erase(ranges.begin(), ranges.begin() + n);
    }
}
void QuickSort::QuickSortStack(std::vector<int> &arr, int l, int r) {
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

void QuickSort::ParallelQuickSortRecursive(std::vector<int> &arr, int l, int r, int level) {
    if (level < 3) {
            std::pair <int, int> border = Partition(arr, l, r);
            int pivot = border.first - 1;
            std::thread thr1(ParallelQuickSortRecursive, std::ref(arr), l, pivot, level + 1);
            std::thread thr2(ParallelQuickSortRecursive, std::ref(arr), pivot, r, level + 1);
            thr1.join();
            thr2.join();
    } else {
        QuickSortRecursive(arr, l, r);
    }
}
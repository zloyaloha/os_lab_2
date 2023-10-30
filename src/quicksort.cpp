#include "quicksort.h"

QuickSort::QuickSort(std::ifstream &file) {
    if (!file) {
        perror("file isn't open");
    }
    std::string s;
    for(file >> s; !file.eof(); file >> s) 
        _array.push_back(std::stoi(s));
}

QuickSort::QuickSort(const std::initializer_list<int> &list) {
    for (const auto &c: list) {
        _array.push_back(c);
    }
}

QuickSort::QuickSort(const std::vector<int> &v) {
    for(const int &num: v) 
        _array.push_back(num);
}

QuickSort::QuickSort(QuickSort &other) {
    for (int i = 0; i < other._array.size(); i++) {
        _array.push_back(other._array[i]);
    }
}

std::ostream &operator << (std::ostream &os, const QuickSort &a) {
    for (size_t i = 0; i < a._array.size(); ++i) {
        os << a._array[i] << ' ';
    }
    os << '\n';
    return os;
}

bool QuickSort::operator==(const QuickSort &other) const{
    if (_array.size() != other._array.size()) {
        return false;
    } else {
        for (size_t i = 0; i < _array.size(); ++i) {
            if (_array[i] != other._array[i]) return false;
        }
    }
    return true;
}

void QuickSort::print(int l, int r) {
    for (size_t i = l; i < r; ++i) {
        std::cout << _array << ' ';
    }
    std::cout << '\n';
} 

void QuickSort::swap(int &a, int&b) {
     int tmp = a;
     a = b;
     b = tmp;
}

std::pair<int,int> QuickSort::Partition(const int &left, const int &right) {
    int medium = _array[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (_array[i] < medium) {
            i++;
        }
        while (_array[j] > medium) {
            j--;
        }
        if (i <= j) {
            swap(_array[i++], _array[j--]);
        }
    }
    return std::make_pair(i, j);
}

void QuickSort::QuickSortRecursive(int l, int r) {
    std::pair <int, int> border;
    border = Partition(l, r);
    if (border.first < r) QuickSortRecursive(border.first, r);
    if (border.first > l) QuickSortRecursive(l, border.second);
}

int QuickSort::size() {
    return _array.size();
}

void QuickSort::mergeArrays(int left, int mid, int right) { 
    int i = 0, j = 0;
    std::vector <int> res;
    while (left + i < mid && mid + j < right) { 
        if (_array[i + left] < _array[mid + j]) {
            res.push_back(_array[left + i]);
            i++;
        } else {
            res.push_back(_array[mid + j]);
            j++;
        }
    }
    while (i + left < mid) {
        res.push_back(_array[left + i]);
        i++;
    }
    while (mid + j < right) {
        res.push_back(_array[mid + j]);
        j++;
    }

    for (int it = 0; it < i + j; it++) {
        _array[left + it] = res[it];
    }
}


void QuickSort::ParallelQuickSort(int l, int r, int num) {
    std::vector<std::thread> thsS;
    std::vector<std::thread> thsM;
    std::vector<std::pair<int, int>>ranges;
    for (int i = 0; i < num; ++i) {
        ranges.push_back(std::pair<int, int> {int(i * ceil(_array.size() / num)), int((i + 1) * ceil(_array.size() / num) - 1)});
        thsS.push_back(std::thread(&QuickSort::QuickSortRecursive, this, int(i * ceil(_array.size() / num)), int((i + 1) * ceil(_array.size() / num) - 1)));
    }
    for (auto & th : thsS) th.join();
    // while (ranges.size() > 1) {
    //     int n = ranges.size();
    //     for (int i = 0; i < n; i += 2) {
    //         thsM.push_back(std::thread(&QuickSort::mergeArrays, this, ranges[i].first, ranges[i+1].first, ranges[i+1].second + 1));
    //         ranges.push_back(std::pair<int,int> {ranges[i].first, ranges[i+1].second});
    //     }
    //     for (auto & th1 : thsM) th1.join();
    //     thsM.clear();
    //     ranges.erase(ranges.begin(), ranges.begin() + n);
    // }
}
void QuickSort::QuickSortStack(int l, int r) {
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
        border = Partition(bord.first, bord.second);
        if (border.first < r) s.push(std::pair(border.first, r));
        if (border.first > l) s.push(std::pair(l, border.second));
    }
}

void QuickSort::ParallelQuickSortRecursive(int l, int r, int level) {
    if (level < 3) {
            std::pair <int, int> border = Partition(l, r);
            int pivot = border.first - 1;
            std::thread thr1(&QuickSort::ParallelQuickSortRecursive, this, l, pivot, level + 1);
            std::thread thr2(&QuickSort::ParallelQuickSortRecursive, this, pivot, r, level + 1);
            thr1.join();
            thr2.join();
    } else {
        QuickSortRecursive(l, r);
    }
}
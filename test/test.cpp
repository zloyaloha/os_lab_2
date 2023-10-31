#include <gtest/gtest.h>
#include "quicksort.h"

TEST(test_01, ConstructorTest) {   
    std::vector a{3,1,2,5,7,1,2,3};
    std::vector b{3,5,2,3,7,31,1,3};
    ASSERT_TRUE((a==b)==false);
}

TEST(test_02, ConstructorTest) {
    std::vector a{3,1,2,5,7,1,2,3};
    ASSERT_TRUE((a==a)==true);
}

TEST(test_01, QSTest) {
    QuickSort a({3,1,2,31,7,1,2,3});
    QuickSort b({1,3,7,1,2,31,2,3});
    b.QuickSortRecursive(0, a.size() - 1);
    a.QuickSortRecursive(0, a.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_02, QSTest) {
    QuickSort a({3,1,2,31,7,1,2,3});
    QuickSort b({1,3,7,1,2,31,2,3});
    a.QuickSortRecursive(0, a.size() - 1);
    b.QuickSortRecursive(0, b.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_03, QSTest) {
    QuickSort a({4,5,0,-100,3,4,5,2,1,3,4,65,12,4});
    QuickSort b({-100, 0, 1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 12, 65});
    a.QuickSortStack(0, a.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_04, QSTest) {
    QuickSort a({-7,12,34,12,98,55,63,1,2,-89,42,42,42,87,19,0,0});
    QuickSort b({-89, -7, 0, 0, 1, 2, 12, 12, 19, 34, 42, 42, 42, 55, 63, 87, 98});
    a.ParallelQuickSort(0, a.size() - 1, 16);
    b.ParallelQuickSortRecursive(0, b.size() - 1, 8);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_05, QSTest) {
    QuickSort a({-7,12,34,12,98,55,63,1,2,-89,42,42,42,87,19,0,0});
    QuickSort b({-89, -7, 0, 0, 1, 2, 12, 12, 19, 34, 42, 42, 42, 55, 63, 87, 98});
    a.ParallelQuickSortRecursive(0, a.size() - 1, 16);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_06, QSTest) {
    QuickSort a({-78,-90,-78,-98,-7,-9,-4,-5,-23,-25,-67,-90,-89});
    QuickSort b({-98, -90, -90, -89, -78, -78, -67, -25, -23, -9, -7, -5, -4});
    a.ParallelQuickSort(0, a.size() - 1, 6);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_07, QSTest) {
    QuickSort a({-78,-90,-78,-98,-7,-9,-4,-5,-23,-25,-67,-90,-89});
    QuickSort b({-98, -90, -90, -89, -78, -78, -67, -25, -23, -9, -7, -5, -4});
    a.QuickSortStack(0, a.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_08, QSTest) {
    QuickSort a({-78,-90,-78,-98,-7,-9,-4,-5,-23,-25,-67,-90,-89});
    QuickSort b({-98, -90, -90, -89, -78, -78, -67, -25, -23, -9, -7, -5, -4});
    a.QuickSortRecursive(0, a.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
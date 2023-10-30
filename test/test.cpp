#include <gtest/gtest.h>
#include "quicksort.h"

TEST(test_01_01, basic_test_set) {   
    std::vector a{3,1,2,5,7,1,2,3};
    std::vector b{3,5,2,3,7,31,1,3};
    ASSERT_TRUE((a==b)==false);
}

TEST(test_01_02, basic_test_set) {
    std::vector a{3,1,2,5,7,1,2,3};
    ASSERT_TRUE((a==a)==true);
}

TEST(test_02_01, basic_test_set) {
    QuickSort a({3,1,2,31,7,1,2,3});
    QuickSort b({1,3,7,1,2,31,2,3});
    a.QuickSortRecursive(0, a.size() - 1);
    b.QuickSortRecursive(0, b.size() - 1);
    ASSERT_TRUE((a==b)==true);
}

TEST(test_02_02, basic_test_set) {
    QuickSort a({3,1,2,5,7,1,2,3});
    ASSERT_TRUE((a==a)==true);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
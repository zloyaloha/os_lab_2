cmake_minimum_required(VERSION 3.10)
project(os_lab_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${INCLUDE_DIR})

add_executable(quick_sort.exe main.cpp ${SOURCE_DIR}/quicksort.cpp)

enable_testing()
add_executable(tests_exe ${TEST_DIR}/test.cpp  ${SOURCE_DIR}/quicksort.cpp)
target_link_libraries(tests_exe ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests_exe)
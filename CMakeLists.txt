project(
    connect
    LANGUAGES CXX
    DESCRIPTION "An AI based solver for Connect-4"
)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

add_library(board STATIC connect/Board.cpp connect/Board.hpp)

# Enabling CTest and finding GTest
enable_testing()
find_package(GTest REQUIRED)

# Board test setup.
add_executable(board_test connect/Board.test.cpp)
target_link_libraries(board_test board GTest::gtest GTest::gtest_main)

gtest_discover_tests(board_test)

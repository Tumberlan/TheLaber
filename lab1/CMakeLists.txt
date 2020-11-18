cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
add_executable(lab1 main.cpp rna.h rna.cpp tests.cpp)
target_link_libraries(lab1 gtest gtest_main)
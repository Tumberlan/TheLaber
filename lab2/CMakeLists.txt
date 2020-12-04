cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
add_executable(lab2 main.cpp game.h game.cpp tests.cpp)
target_link_libraries(lab2 gtest gtest_main)

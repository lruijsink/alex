cmake_minimum_required(VERSION 3.10.2)
project(alex)

set(CMAKE_CXX_FLAGS "-std=c++20")

add_executable(example_basic example/basic.cpp)
target_include_directories(example_basic PRIVATE include)

cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)

project(alex)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
include_directories(include)

add_executable(constexpr_example example/constexpr.cpp)

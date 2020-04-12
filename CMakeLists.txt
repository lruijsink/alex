cmake_minimum_required(VERSION 3.11.0)

project(range_experiments)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
    
#------------------------------------------------------------------------------
# This project

include_directories(include)

add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(bench)

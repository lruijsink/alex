cmake_minimum_required(VERSION 3.1.0)
project(alex)

#------------------------------------------------------------------------------
# C++

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

#------------------------------------------------------------------------------
# targets

add_subdirectory(example)
add_subdirectory(test)

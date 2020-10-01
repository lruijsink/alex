cmake_minimum_required(VERSION 3.1.0)
project(alex CXX)

enable_testing()

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

#------------------------------------------------------------------------------
# C++

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

#------------------------------------------------------------------------------
# targets

add_subdirectory(example)
add_subdirectory(test)

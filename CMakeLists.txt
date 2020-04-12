cmake_minimum_required(VERSION 3.1.0)

project(clang_crash)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
project(alex_benchmarks)

# GoogleBench dependency
include(FetchContent)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(crash "crash.cpp")

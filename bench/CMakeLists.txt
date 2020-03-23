project(alex_benchmarks)

#------------------------------------------------------------------------------
# GoogleBench dependency

include(FetchContent)
    
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git)

# Prevent problems with linking  
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Don't include googlebenchmark unit tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

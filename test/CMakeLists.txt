project(alex_tests)

#------------------------------------------------------------------------------
# GoogleTest dependency

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git)

# Prevent problems with linking  
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories(${gmock_SOURCE_DIR}/include)

#------------------------------------------------------------------------------
# Tests

enable_testing()

function(alex_test test_name)
    add_executable       (alex_${test_name} alex/${test_name}.cpp)
    target_link_libraries(alex_${test_name} gtest_main)
    add_test             (alex_${test_name} ${test_name})
endfunction()

alex_test("test_grammar")
alex_test("test_stream_forker")
alex_test("test_stream_range")

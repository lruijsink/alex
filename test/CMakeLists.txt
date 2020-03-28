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

function(unit_test test_name)
    add_executable(test_${test_name} alex/test_${test_name}.cpp)
    target_link_libraries(test_${test_name} gtest_main)
    add_test(test_${test_name} test_${test_name})
endfunction()

unit_test("any")
unit_test("any_but")
unit_test("eof")
unit_test("from_to")
unit_test("grammar")
unit_test("grammar_abstract")
unit_test("literal")
unit_test("one_of")
unit_test("optional")
unit_test("repeat")

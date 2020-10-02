cmake_minimum_required(VERSION 3.1.0)
project(alex_test)

function(unit_test test_name)
    add_executable(test_${test_name} test_${test_name}.cpp)
    target_link_libraries(test_${test_name} Catch2::Catch2)
    catch_discover_tests(test_${test_name})
endfunction()

unit_test(basic)

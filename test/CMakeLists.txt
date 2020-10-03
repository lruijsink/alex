# Adds test/test_{test_name}.cpp as a unit test
function(unit_test test_name)
    add_executable(test_${test_name} test_${test_name}.cpp)
    target_link_libraries(test_${test_name} Catch2::Catch2)
    catch_discover_tests(test_${test_name})
endfunction()

unit_test(basic)

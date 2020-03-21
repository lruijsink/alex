project(alex_tests)

add_executable       (alex_parser_test lt3/alex/parser_test.cpp)
target_link_libraries(alex_parser_test gtest_main)
add_test             (alex_parser_test alex_parser_test)

add_executable       (alex_range_stream_test lt3/alex/range_stream_test.cpp)
target_link_libraries(alex_range_stream_test gtest_main)
add_test             (alex_range_stream_test alex_range_stream_test)

add_executable       (alex_stream_forker_test lt3/alex/stream_forker_test.cpp)
target_link_libraries(alex_stream_forker_test gtest_main)
add_test             (alex_stream_forker_test alex_stream_forker_test)

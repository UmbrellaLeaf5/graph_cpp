file(GLOB_RECURSE lib_source_list "*.cpp" "*.hpp")

add_library(graph_cpp ${lib_source_list})

target_include_directories(graph_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

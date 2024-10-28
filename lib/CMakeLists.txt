file(GLOB_RECURSE LIB_SOURCES "*.cpp" "*.hpp")

add_library(graph_cpp ${LIB_SOURCES})

target_include_directories(graph_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

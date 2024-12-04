cmake_minimum_required(VERSION 3.10)
project(graph_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp" "src/*.hpp")

add_library(${PROJECT_NAME} ${LIB_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

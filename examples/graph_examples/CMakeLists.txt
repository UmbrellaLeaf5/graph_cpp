cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE source_list "*.cpp" "*.hpp")
file(GLOB_RECURSE lib_source_list "../../lib/*.cpp" "../../lib/*.hpp")
file(GLOB_RECURSE main_source_list "main.cpp")

include_directories(${PROJECT_NAME} PUBLIC src)
include_directories(${PROJECT_NAME} PUBLIC ../../lib/)

add_executable(${PROJECT_NAME} ${source_list})
target_link_libraries(${PROJECT_NAME} PUBLIC graph_cpp)

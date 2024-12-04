cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

include_directories(${PROJECT_NAME} PUBLIC src)

add_executable(${PROJECT_NAME}_examples ${SOURCES})

find_library(graph_cpp ../)
target_link_libraries(${PROJECT_NAME}_examples PUBLIC graph_cpp)

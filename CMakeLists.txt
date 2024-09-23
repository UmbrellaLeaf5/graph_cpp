cmake_minimum_required(VERSION 3.20)

project(graph_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++20 -O2")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
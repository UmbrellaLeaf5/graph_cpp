cmake_minimum_required(VERSION 3.20)

project(homeworks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17 -O2")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sandbox)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/additional_tasks)

file(GLOB_RECURSE tasks_dirs LIST_DIRECTORIES true ".")

foreach(dir ${tasks_dirs})
  IF(IS_DIRECTORY ${dir})
    IF(${dir} MATCHES "task_0[0-9]$" AND NOT ${dir} MATCHES "build")
      add_subdirectory(${dir})
    ENDIF()
  ELSE()
    CONTINUE()
  ENDIF()
endforeach()
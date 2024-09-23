cmake_minimum_required(VERSION 3.10)

project(examples)

file(GLOB_RECURSE tasks_dirs LIST_DIRECTORIES true ".")

foreach(dir ${tasks_dirs})
  IF(IS_DIRECTORY ${dir})
    IF(NOT ${dir} MATCHES ".*src.*")
      add_subdirectory(${dir})
    ENDIF()
  ELSE()
    CONTINUE()
  ENDIF()
endforeach()

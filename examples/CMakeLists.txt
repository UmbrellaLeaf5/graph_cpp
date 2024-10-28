cmake_minimum_required(VERSION 3.10)

project(examples LANGUAGES CXX)

file(GLOB_RECURSE DIRS LIST_DIRECTORIES true ".")

foreach(DIR ${DIRS})
  IF(IS_DIRECTORY ${DIR})
    IF(NOT ${DIR} MATCHES ".*src.*")
      add_subdirectory(${DIR})
    ENDIF()
  ELSE()
    CONTINUE()
  ENDIF()
endforeach()

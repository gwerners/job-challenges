cmake_minimum_required(VERSION 3.5.1)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -std=c++14")

project (sudoku)
add_executable(sudoku main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    target_link_libraries(sudoku pthread)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")


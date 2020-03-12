cmake_minimum_required(VERSION 3.5.1)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -std=c++14")

project (bench_string_invert)
include_directories("benchmark/include")
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(bench_string_invert main.cpp invert.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    target_link_libraries(bench_string_invert benchmark pthread)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

project (mock_string_invert)
include_directories("benchmark/include" "benchmark/googletest/googletest/include" "benchmark/googletest/googlemock/include")
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(mock_string_invert main_mock.cpp invert.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    target_link_libraries(mock_string_invert gmock gtest pthread)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

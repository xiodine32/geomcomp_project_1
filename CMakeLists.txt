cmake_minimum_required(VERSION 3.3)
project(geomcomp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(geomcomp ${SOURCE_FILES})
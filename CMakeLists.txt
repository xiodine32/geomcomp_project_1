cmake_minimum_required(VERSION 3.3)
project(geomcomp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDLmain -lSDL2 -lGL -lGLU")

set(SOURCE_FILES main.cpp engine.cpp engine.h camera.cpp camera.h)
add_executable(geomcomp ${SOURCE_FILES})
# cmake_minimum_required(VERSION <specify CMake version here>)
project(passOne)

set(CMAKE_CXX_STANDARD 11)

add_executable(passOne main.cpp optable.cpp optable.h cmake-build-debug/Row.cpp Row.cpp Row.h validation.cpp validation.h parsing_map.cpp parsing_map.h)




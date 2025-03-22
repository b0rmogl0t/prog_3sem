cmake_minimum_required(VERSION 3.10)
project(MatrixProject LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 17)

add_executable(matrix main.cpp Matrix.hpp)

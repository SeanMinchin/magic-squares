cmake_minimum_required(VERSION 3.10)
project(magic_squares)

set(CMAKE_CXX_STANDARD 17)

add_executable(magic_squares magic_squares.cpp magic_squares.hpp matrix.hpp)
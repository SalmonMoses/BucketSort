cmake_minimum_required(VERSION 3.14)
project(PancakeSort)

set(CMAKE_CXX_STANDARD 17)

add_executable(PancakeSort main.cpp arr_utils.h arr_utils.cpp utils.cpp utils.h)
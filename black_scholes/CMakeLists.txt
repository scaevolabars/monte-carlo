cmake_minimum_required(VERSION 3.15)
project(black_sholes)

set(CMAKE_CXX_STANDARD 17)

add_executable(black_scholes main.cpp BlackScholes.h BlackScholes.cpp)
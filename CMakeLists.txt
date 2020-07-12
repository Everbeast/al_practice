cmake_minimum_required(VERSION 3.15)
project(algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithm main.cpp dp/fibonacci.cpp dp/LIS.cpp dp/coins.cpp dp/backpack.cpp)
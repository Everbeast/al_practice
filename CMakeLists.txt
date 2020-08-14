cmake_minimum_required(VERSION 3.15)
project(algorithm)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(./dp DIR_SRCS)
add_executable(algorithm ${DIR_SRCS})
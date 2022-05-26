cmake_minimum_required(VERSION 3.19)
project(learn_mpi C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(examples)
add_subdirectory(exam2021)
add_subdirectory(exercise)
#add_executable(learn_mpi main.c)
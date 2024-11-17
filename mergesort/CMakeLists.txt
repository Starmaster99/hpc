cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(benchmarking VERSION 1.0.0)
file(MAKE_DIRECTORY bin/)
add_executable(benchmarking src/mergesort.cpp)
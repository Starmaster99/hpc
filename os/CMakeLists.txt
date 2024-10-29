cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-omit-frame-pointer -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

project(os LANGUAGES C CXX)

file(MAKE_DIRECTORY bin/)

add_executable(${PROJECT_NAME} src/task1.1.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin/)
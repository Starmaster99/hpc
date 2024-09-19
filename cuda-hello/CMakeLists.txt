cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CUDA_HOST_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CUDA_ARCHITECTURES 75)    # Turing

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-omit-frame-pointer -rdynamic")
set(CMAKE_CUDA_FLAGS_DEBUG "-G -g")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3")

project(CUDAhello LANGUAGES CXX CUDA)

file(MAKE_DIRECTORY bin/)

add_executable(${PROJECT_NAME} src/hello.cu)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin/)

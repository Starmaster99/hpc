cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-omit-frame-pointer -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

project(mergesort LANGUAGES C CXX)

file(MAKE_DIRECTORY bin/)

add_executable(${PROJECT_NAME}-seq src/mergesort_seq.cpp)
add_executable(${PROJECT_NAME}-par src/mergesort_par.cpp)

#add_executable(hempsort src/hempsort.cpp)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_compile_options(${PROJECT_NAME}-par PUBLIC ${OpenMP_CXX_FLAGS})
    target_link_libraries(${PROJECT_NAME}-par PUBLIC ${OpenMP_CXX_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME}-seq DESTINATION ${PROJECT_SOURCE_DIR}/bin/)
install(TARGETS ${PROJECT_NAME}-par DESTINATION ${PROJECT_SOURCE_DIR}/bin/)
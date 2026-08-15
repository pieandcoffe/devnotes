cmake_minimum_required(VERSION 3.10)
project(assignment_01)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(assignment_01 src/main.cpp src/analysis.cpp
        src/debugging.cpp)

target_include_directories(assignment_01 PRIVATE include)

target_compile_options(assignment_01 PRIVATE -Wall -Wextra -Wpedantic)

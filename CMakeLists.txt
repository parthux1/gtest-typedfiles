# Version requirement
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project("gtest-typedfiles" VERSION 0.1.0)

# code
add_subdirectory("src")
add_subdirectory("test")
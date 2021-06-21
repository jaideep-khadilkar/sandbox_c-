
set(CMAKE_VERBOSE_MAKEFILE ON)

cmake_minimum_required(VERSION 3.12)

# set the project name
project(sandbox_cpp VERSION 1.0 LANGUAGES CXX C)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("stl")
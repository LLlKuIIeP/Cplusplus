cmake_minimum_required(VERSION 3.15)

project(untitled1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled1 main.cpp)

#target_compile_options(untitled1 PUBLIC cxx_std_17)

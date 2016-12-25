cmake_minimum_required(VERSION 2.8)

project(final)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_definitions(${CMAKE_CXX_FLAGS})

add_executable(final final.cpp)

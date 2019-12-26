cmake_minimum_required(VERSION 3.5)

project(wangleEchoServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS thread)
find_package(gflags REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(folly CONFIG REQUIRED)
find_package(fizz CONFIG REQUIRED)
find_package(wangle REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Boost::thread
    fmt::fmt
    fmt::fmt-header-only
    Folly::folly
    Folly::folly_deps
    Folly::follybenchmark
    fizz::fizz
    wangle::wangle
)

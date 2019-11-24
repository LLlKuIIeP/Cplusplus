cmake_minimum_required(VERSION 3.5)

project(testNNG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(/home/user/nng ${CMAKE_CURRENT_BINARY_DIR}/nng)

add_executable(testNNG main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC /home/user/nng/include/nng/compat)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nng
    )

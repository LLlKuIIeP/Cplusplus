cmake_minimum_required(VERSION 3.5)

project(testNNG2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(C:/Repositories/nng ${CMAKE_CURRENT_BINARY_DIR}/nng)

add_executable(testNNG2 main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC C:/Repositories/nng/include/nng/compat)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nng
    )

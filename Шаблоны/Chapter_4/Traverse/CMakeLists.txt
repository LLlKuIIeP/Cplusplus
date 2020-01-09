cmake_minimum_required(VERSION 3.5)

project(Traverse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

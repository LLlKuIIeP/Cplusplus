cmake_minimum_required(VERSION 3.15)

project(testWinToast LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 REQUIRED COMPONENTS Core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(HEADER
./wintoast/wintoastlib.h
)

set(SOURCE
./wintoast/wintoastlib.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${HEADER} ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ./)
target_link_libraries(${PROJECT_NAME} PRIVATE 
Qt5::Core
)
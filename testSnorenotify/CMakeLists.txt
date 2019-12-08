cmake_minimum_required(VERSION 3.5)

project(testSnorenotify LANGUAGES CXX)
find_package(LibsnoreQt5 0.7.0 REQUIRED)
find_package(LibsnoreSettingsQt5 0.7.0 REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(RESOURCES
   ./src.qrc
)

add_executable(${PROJECT_NAME} main.cpp ${RESOURCES})

add_subdirectory(C:/Repositories/snoretoast ${CMAKE_CURRENT_BINARY_DIR}/snoretoast)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Snore::Libsnore
  Snore::LibsnoreSettings
)

set_target_properties(snoretoast PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
)
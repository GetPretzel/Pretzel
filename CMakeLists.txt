cmake_minimum_required(VERSION 3.16)

project(Pretzel LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Quick Sql Widgets REQUIRED)

add_subdirectory(thirdparty)

add_subdirectory(src)

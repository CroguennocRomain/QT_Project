cmake_minimum_required(VERSION 3.18)
project(QT_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6Widgets CONFIG REQUIRED)

file (GLOB_RECURSE Projet src/*.cpp src/*.h)

add_executable(QT_Project ${Projet} src/Entity/Character.h src/Entity/Character.cpp)

target_link_libraries(QT_Project Qt6::Widgets)
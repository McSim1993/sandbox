cmake_minimum_required(VERSION 3.9)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

add_executable(sandbox
        src/main.cpp src/Car.cpp src/Car.hpp src/Wall.cpp src/Wall.hpp src/Application.cpp src/Application.hpp)

target_link_libraries(sandbox sfml-graphics)
target_link_libraries(sandbox sfml-window)
target_link_libraries(sandbox sfml-system)
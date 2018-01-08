cmake_minimum_required(VERSION 3.9)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(sandbox
        src/main.cpp src/Car.cpp src/Car.hpp src/Wall.cpp src/Wall.hpp src/Application.cpp src/Application.hpp src/VectorUtils.cpp)

add_executable(tests
        src/VectorUtils.cpp src/tests/VectorUtilsSpec.cpp)

target_link_libraries(sandbox sfml-graphics sfml-window sfml-system)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
cmake_minimum_required(VERSION 4.1)
project(tetris)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(SDL2 REQUIRED)

add_executable(MyGame main.cpp)

target_link_libraries(MyGame PRIVATE SDL2::SDL2)
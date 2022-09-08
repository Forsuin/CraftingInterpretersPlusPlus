cmake_minimum_required(VERSION 3.23)
project(CraftingInterpreters)

set(CMAKE_CXX_STANDARD 20)

add_executable(CraftingInterpreters src/main.cpp src/lox.cpp src/lox.hpp)

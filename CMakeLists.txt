cmake_minimum_required(VERSION 3.23)
project(CraftingInterpreters)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_executable(CraftingInterpreters cSrc/main.c cSrc/common.h cSrc/chunk.h cSrc/memory.h cSrc/memory.c cSrc/chunk.c cSrc/debug.h cSrc/debug.c cSrc/value.h cSrc/value.c)
add_executable(CraftingInterpretersPlusPlus cppSrc/main.cpp cppSrc/lox.cpp cppSrc/lox.hpp cppSrc/tokenType.hpp cppSrc/tokenType.cpp cppSrc/Token.hpp cppSrc/scanner.cpp cppSrc/scanner.hpp cppSrc/loxError.cpp cppSrc/loxError.hpp)

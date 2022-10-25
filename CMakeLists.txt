cmake_minimum_required(VERSION 3.13...3.23)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
            "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
endif()

project(CraftingInterpreters LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin") #keep all runtime files in one directory

file(
        GLOB_RECURSE SOURCE_FILES
        CONFIGURE_DEPENDS #Automatically reconfigure if source files are added/removed
        ${PROJECT_SOURCE_DIR}/cppSrc/*.cpp
        ${PROJECT_SOURCE_DIR}/cppSrc/*.hpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Enforce UTF-8 on MSVC
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

find_package(fmt CONFIG REQUIRED)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        fmt::fmt
)
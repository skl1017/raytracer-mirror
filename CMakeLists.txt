cmake_minimum_required(VERSION 3.20)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2 COMPONENTS graphics window system QUIET)
if(NOT SFML_FOUND)
    set(SFML_STATIC_LIBRARIES ON)
    find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
endif()

add_executable(raytracer
    src/main.cpp
    src/Display.cpp
)

target_include_directories(raytracer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(raytracer PRIVATE sfml-graphics)

target_compile_options(raytracer PRIVATE -Wall -Wextra -Wpedantic)

option(DEBUG "Compile with -g3" OFF)
if(DEBUG)
    target_compile_options(raytracer PRIVATE -g3)
endif()

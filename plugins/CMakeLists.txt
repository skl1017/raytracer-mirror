cmake_minimum_required(VERSION 3.13)
project(plugins)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ../lib)

include_directories(
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/plugins
    ${CMAKE_SOURCE_DIR}/src
)

# === Sphere ===

set(SPHERE
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Sphere/Sphere.cpp
)

add_library(sphere SHARED ${SPHERE})

target_include_directories(sphere PRIVATE
    ${CMAKE_SOURCE_DIR}/Sphere
)

# === Rectangle ===

set(RECTANGLE
    plugins/Primitives/Rectangle/Rectangle.cpp
)

add_library("rectangle" SHARED ${SPHERE})

target_include_directories(rectangle PRIVATE
    ${CMAKE_SOURCE_DIR}/Rectangle
)

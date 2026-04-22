cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

target_compile_definitions(sphere PRIVATE
    LIB_PATH="${PROJECT_SOURCE_DIR}/libs/Primitives"
)

set_target_properties(sphere PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/Primitives
)

# === Rectangle ===

set(RECTANGLE
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Rectangle/Rectangle.cpp
)

add_library("rectangle" SHARED ${RECTANGLE})

target_include_directories(rectangle PRIVATE
    ${CMAKE_SOURCE_DIR}/Rectangle
)

set_target_properties(rectangle PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/Primitives
)
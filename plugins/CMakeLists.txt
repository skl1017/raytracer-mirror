cmake_minimum_required(VERSION 3.13)
project(plugins)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ../lib)

include_directories(${CMAKE_SOURCE_DIR}/shared)

# === Sphere ===

set(SPHERE
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Sphere/Sphere.cpp
)

add_library(sphere SHARED ${SPHERE})

target_include_directories(sphere PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/plugins
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Sphere
)

set_target_properties(sphere PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/Primitives
)

# === PointLight ===

set (POINTLIGHT
    ${CMAKE_SOURCE_DIR}/plugins/Lights/PointLight/PointLight.cpp)

add_library(pointLight SHARED ${POINTLIGHT})

target_include_directories(pointLight PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/plugins
)

set_target_properties(pointLight PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/Lights)

# === Plane ===

set(PLANE
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Plane/Plane.cpp
)

add_library("plane" SHARED ${PLANE})

target_include_directories(plane PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/plugins
    ${CMAKE_SOURCE_DIR}/plugins/Primitives/Plane
)


set_target_properties(plane PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/Primitives
)

# === DirectionaLight ===

set (DIRECTIONALLIGHT
    ${CMAKE_SOURCE_DIR}/plugins/Lights/Directional/DirectionalLight.cpp)

add_library(directionalLight SHARED ${DIRECTIONALLIGHT})

target_include_directories(directionalLight PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/plugins
)

set_target_properties(directionalLight PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/Lights)



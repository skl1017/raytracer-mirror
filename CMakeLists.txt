cmake_minimum_required(VERSION 3.20)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/shared/)

set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2 COMPONENTS graphics window system QUIET)
if(NOT SFML_FOUND)
    set(SFML_STATIC_LIBRARIES ON)
    find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
endif()

set(RAYTRACER
    src/Camera/Camera.cpp
    src/Core/Core.cpp
    src/Display/Display.cpp
    src/Renderer/Renderer.cpp
    src/Scene/Scene.cpp
)

add_executable(raytracer ${RAYTRACER} src/main.cpp)

target_include_directories(raytracer PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/plugins
)

target_compile_options(raytracer PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(raytracer PRIVATE
    sfml-graphics
)

if(DEBUG)
    target_compile_options(raytracer PRIVATE -g3)
endif()

add_subdirectory(plugins)

target_link_libraries(raytracer PRIVATE sphere)

cmake_minimum_required(VERSION 3.13)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEBUG "Compile with -g3" OFF)

include_directories(${PROJECT_SOURCE_DIR}/shared/)

set(RAYTRACER
    ${PROJECT_SOURCE_DIR}/src/Camera/Camera.cpp
    ${PROJECT_SOURCE_DIR}/src/Core/Core.cpp
    ${PROJECT_SOURCE_DIR}/src/Display/Display.cpp
    ${PROJECT_SOURCE_DIR}/src/Scene/Scene.cpp
)

add_executable(raytracer ${RAYTRACER} src/main.cpp)

target_include_directories(raytracer PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(raytracer PRIVATE
    -Wall
    -Wextra
)

target_link_libraries(raytracer PRIVATE config++.a)

if(DEBUG)
    target_compile_options(raytracer PRIVATE -g3)
endif()

add_subdirectory(plugins)
add_subdirectory(tests)
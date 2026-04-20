cmake_minimum_required(VERSION 3.13)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer src/main.cpp
)

option(DEBUG "Compile with -g3" OFF)

target_include_directories(raytracer PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(raytracer PRIVATE
    -Wall
    -Wextra
)

target_link_libraries(raytracer PRIVATE config++.a)


if(DEBUG)
    target_compile_options(raytracer PRIVATE -g3)
endif()

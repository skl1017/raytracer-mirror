cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(RayTracer)
add_executable(raytracer
    src/main.cpp
)
target_link_libraries(raytracer PRIVATE config++.a)
target_include_directories(raytracer PRIVATE include)

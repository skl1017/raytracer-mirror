cmake_minimum_required(VERSION 3.20)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/shared/)

set(RAYTRACER
    ${PROJECT_SOURCE_DIR}/src/Camera/Camera.cpp
    ${PROJECT_SOURCE_DIR}/src/Display/Display.cpp
    ${PROJECT_SOURCE_DIR}/src/Scene/Scene.cpp
    ${PROJECT_SOURCE_DIR}/src/PluginFactory/PluginFactory.cpp

)

add_executable(raytracer ${RAYTRACER} src/main.cpp)

target_link_options(raytracer PRIVATE -Wl,--export-dynamic)

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

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(raytracer
    sfml-graphics sfml-window sfml-system sfml-audio
    config++.a
)

if(DEBUG)
    target_compile_options(raytracer PRIVATE -g3)
endif()

add_subdirectory(plugins)
add_subdirectory(tests)

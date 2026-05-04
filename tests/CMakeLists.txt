cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}/shared/
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/plugins
)

set(TESTS
    ${RAYTRACER}
    ${PROJECT_SOURCE_DIR}/tests/test_dlloader.cpp
)

add_executable(test_binary ${TESTS})

target_compile_options(test_binary PRIVATE
    -Wall
    -Wextra
    -g3
)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(test_binary PRIVATE
    sfml-graphics sfml-window sfml-system sfml-audio
    config++.a
    criterion
    sphere
)
target_link_options(test_binary PRIVATE -Wl,--export-dynamic)

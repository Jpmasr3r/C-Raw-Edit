cmake_minimum_required(VERSION 3.10)

project(main C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/dynamic-Strings)

add_executable(main src/main.c src/utils.c src/editor.c)

target_link_libraries(main dynamic_strings)
target_include_directories(main PRIVATE include)
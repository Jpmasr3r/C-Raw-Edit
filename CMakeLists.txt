cmake_minimum_required(VERSION 3.10)

project(main C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  dynamic_strings
  GIT_REPOSITORY https://github.com/Jpmasr3r/C-Dynamic-Strings
  GIT_TAG main
)

FetchContent_MakeAvailable(dynamic_strings)

add_executable(main src/main.c src/utils.c src/editor.c)

target_link_libraries(main PRIVATE dynamic_strings)
target_include_directories(main PRIVATE include)
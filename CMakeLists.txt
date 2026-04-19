cmake_minimum_required(VERSION 3.10)

project(main C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.c src/utils.c src/dynamic_strings.c src/editor.c)

# target_compile_options(main PRIVATE
#     -Wall
#     -Wextra
#     -Werror
#     $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer>
#     $<$<CONFIG:Release>:-O2 -DNDEBUG>
# )

target_include_directories(main PRIVATE include)
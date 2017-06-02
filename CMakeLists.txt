cmake_minimum_required(VERSION 3.7)
project(minifs)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c filesystem.c filesystem.h file_allocation_table.c file_allocation_table.h command_interpreter.c command_interpreter.h)
add_executable(minifs ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.7)
project(minifs)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(minifs ${SOURCE_FILES})
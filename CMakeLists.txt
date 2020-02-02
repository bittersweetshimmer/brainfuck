cmake_minimum_required(VERSION 3.16)

project(brainfuck)

set(SOURCES "./src/main.cpp" "./src/brainfuck/parse.cpp" "./src/brainfuck/State.cpp")

add_executable(brainfuck ${SOURCES})
set_property(TARGET brainfuck PROPERTY CXX_STANDARD 20)
target_include_directories(brainfuck PUBLIC "./include/")

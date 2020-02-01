cmake_minimum_required(VERSION 3.16)

project(brainfuck)

set(SOURCES "./src/main.cpp" "./src/brainfuck/parse.cpp" "./src/brainfuck/State.cpp")

add_executable(brainfuck ${SOURCES})
target_include_directories(brainfuck "./include/")

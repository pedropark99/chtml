cmake_minimum_required(VERSION 3.5)

project(chtml C)
include_directories(src)
add_executable(chtml src/tokenizer.c)

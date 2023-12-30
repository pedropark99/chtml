cmake_minimum_required(VERSION 3.5)

project(chtml C)
include_directories(src)
set(CMAKE_BUILD_TYPE Debug)
add_executable(chtml
	       src/parser.c 
	       src/tokenizer.c)

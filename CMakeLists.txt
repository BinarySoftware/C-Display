cmake_minimum_required(VERSION 3.18)
project(C-Display C)

set(CMAKE_C_STANDARD 11)

add_executable(C-Display main.c display.h display.c animate.h animate.c color.h color.c)

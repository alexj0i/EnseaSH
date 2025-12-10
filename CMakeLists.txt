cmake_minimum_required(VERSION 4.1)
project(EnseaSH C)

set(CMAKE_C_STANDARD 11)

add_executable(EnseaSH main.c
        question1.c
        question1.h
        question2.c
        question2.h
        question3.c
        question3.h
)

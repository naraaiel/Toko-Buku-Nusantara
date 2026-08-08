cmake_minimum_required(VERSION 4.2)
project(Menu1_TokoBukuNusantara C)

set(CMAKE_C_STANDARD 11)

add_library(Menu1_TokoBukuNusantara STATIC library.c
        "menu 3.c")

cmake_minimum_required(VERSION 3.7)
project(mtm3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c
        list.h
        list_mtm1.h
        set.h
        mtm_ex3.h
        list_mtm1.c)
add_executable(mtm3 ${SOURCE_FILES})
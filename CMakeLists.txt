cmake_minimum_required(VERSION 3.7)
project(mtm3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Company.c Company.h list.h EscapeTechnion.c EscapeTechnion.h Room.c Room.h set.h EscapeTechnion.c EscapeTechnion.h)

add_executable(mtm3 ${SOURCE_FILES})

set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")

target_link_libraries(mtm3 ${CMAKE_SOURCE_DIR}/libmtm.a)

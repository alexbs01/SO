cmake_minimum_required(VERSION 3.23)
project(shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(shell
        comandos.c
        comandos.h
        funcionesAuxiliares.c
        funcionesAuxiliares.h
        list_test.c
        lista.c
        lista.h
        main.c)

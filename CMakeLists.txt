cmake_minimum_required(VERSION 3.13)
project(Std_Reader C)

set(CMAKE_C_STANDARD 99)

add_library(Std_Reader SHARED Std_Reader.h Std_Reader.c)
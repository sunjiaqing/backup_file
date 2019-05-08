cmake_minimum_required(VERSION 3.13)
project(backup_file)

set(CMAKE_CXX_STANDARD 17)

add_executable(backup_file main.cpp Config.cpp Config.h JSON.h File.h)


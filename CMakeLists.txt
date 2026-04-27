cmake_minimum_required(VERSION 3.21.1)
project(untitled3 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled3
        waveform.c
        io.c
        main.c)

configure_file(power_quality_log.csv power_quality_log.csv COPYONLY)

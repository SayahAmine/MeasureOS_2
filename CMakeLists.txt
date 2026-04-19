cmake_minimum_required(VERSION 3.26)
project(MeasureOS_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(MeasureOS_2
        main.c
        Kernel.c
        serial.c
        sensors.c
        injector.c
        events.h
)

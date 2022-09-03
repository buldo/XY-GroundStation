cmake_minimum_required(VERSION 3.14)
project(servo
    VERSION 1.0.0
    DESCRIPTION "Servo library"
    LANGUAGES CXX)

add_library(servo) # initialized below
add_library(servo::servo ALIAS servo)

set(sources
    include/pico_servo.hpp
    src/pico_servo.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(servo PRIVATE ${sources})
target_include_directories(servo
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(servo PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(servo PUBLIC 
    pico_stdlib 
    hardware_pwm
    )

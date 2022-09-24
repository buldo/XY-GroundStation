cmake_minimum_required(VERSION 3.14)
project(actuator
    VERSION 1.0.0
    DESCRIPTION "actuator library"
    LANGUAGES CXX)

add_library(actuator) # initialized below
add_library(actuator::actuator ALIAS actuator)

set(sources
    include/pico_servo.hpp
    include/Actuator.hpp
    src/pico_servo.cpp
    src/Actuator.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(actuator PRIVATE ${sources})
target_include_directories(actuator
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(actuator PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(actuator PUBLIC 
    pico_stdlib 
    hardware_pwm
    )

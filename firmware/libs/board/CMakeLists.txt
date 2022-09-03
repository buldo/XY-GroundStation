cmake_minimum_required(VERSION 3.14)
project(station-config
    VERSION 1.0.0
    DESCRIPTION "Station configuration"
    LANGUAGES CXX)

add_library(station-config) # initialized below
add_library(station-config::station-config ALIAS station-config)

set(sources
    include/pin_definitions.hpp
    include/board_startup.hpp
    src/board_startup.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(station-config PRIVATE ${sources})
target_include_directories(station-config
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(station-config PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(station-config PUBLIC 
    pico_stdlib 
    hardware_spi hardware_pwm
    )
cmake_minimum_required(VERSION 3.14)
project(station-lcd
    VERSION 1.0.0
    DESCRIPTION "Station LCD support"
    LANGUAGES CXX)

add_library(station-lcd) # initialized below
add_library(station-lcd::station-lcd ALIAS station-lcd)

set(sources
    include/lcd_1in14.hpp
    src/lcd_1in14.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(station-lcd PRIVATE ${sources})
target_include_directories(station-lcd
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(station-lcd PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(station-lcd PUBLIC 
    pico_stdlib 
    station-config
    )
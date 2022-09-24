cmake_minimum_required(VERSION 3.14)
project(user-interface
    VERSION 1.0.0
    DESCRIPTION "User Interface library"
    LANGUAGES CXX)

add_library(user-interface) # initialized below
add_library(user-interface::user-interface ALIAS user-interface)

set(sources
    include/UserInterface.hpp
    include/KeypadKey.hpp
    include/MainScreen.hpp
    include/SettingsScreen.hpp
    src/UserInterface.cpp
    src/MainScreen.cpp
    src/SettingsScreen.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(user-interface PRIVATE ${sources})
target_include_directories(user-interface
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(user-interface PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(user-interface PUBLIC 
    pico_stdlib
    station-lcd
    lvgl::lvgl
    actuator
    )

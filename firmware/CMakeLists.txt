cmake_minimum_required(VERSION 3.22)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(ground_station C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(ground_station
    main.cpp
)

add_subdirectory(libs/servo)
add_subdirectory(libs/board)
# add_subdirectory(libs/Icm20948)
add_subdirectory(libs/lcd)
add_subdirectory(libs/user_interface)
# add_subdirectory(libs/Fonts)
# add_subdirectory(libs/GUI)

# include_directories(./libs/Config)
# include_directories(./libs/GUI)
# include_directories(./libs/Icm20948)
# include_directories(./libs/LCD)

pico_set_program_name(ground_station "GroundStation")
pico_set_program_version(ground_station "0.1")

pico_enable_stdio_uart(ground_station 0)
pico_enable_stdio_usb(ground_station 1)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(ground_station 
    pico_stdlib
    hardware_dma
    hardware_pio
    hardware_timer
    hardware_clocks
    hardware_pwm
    hardware_spi
    
    servo
    # LCD 
    # Icm20948
    # GUI
    # Fonts
    # Config
    station-config
    station-lcd
    user-interface
    )

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(ground_station)

pico_add_impl_library(servo)

target_include_directories(servo INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(servo INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/pico_servo.cpp
)

target_link_libraries(servo INTERFACE tinyusb_host_base tinyusb_common)
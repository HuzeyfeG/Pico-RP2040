cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(esc_calibration)

pico_sdk_init()

add_executable(esc_calibration
    src/main.cpp
    src/BLDC.cpp
)

target_include_directories(esc_calibration PUBLIC
    inc
)

target_link_libraries(esc_calibration 
    pico_stdlib
    hardware_pwm
    hardware_adc
)

pico_enable_stdio_usb(esc_calibration 1)
pico_enable_stdio_uart(esc_calibration 0)

pico_add_extra_outputs(esc_calibration)
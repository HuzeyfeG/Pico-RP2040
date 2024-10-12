cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(test_dc_motor)

pico_sdk_init()

add_executable(test_dc_motor
    src/DC_MOTOR.cpp
    src/main.cpp
)

target_include_directories(test_dc_motor PUBLIC
    inc
)

target_link_libraries(test_dc_motor
    pico_stdlib
    hardware_pwm
)

pico_enable_stdio_usb(test_dc_motor 1)
pico_enable_stdio_uart(test_dc_motor 0)

pico_add_extra_outputs(test_dc_motor)

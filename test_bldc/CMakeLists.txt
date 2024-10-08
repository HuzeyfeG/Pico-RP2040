cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(test_bldc)

pico_sdk_init()

add_executable(test_bldc
    src/BLDC.cpp
    src/main.cpp
)

target_include_directories(test_bldc PUBLIC
    inc
)

target_link_libraries(test_bldc
    pico_stdlib
    hardware_pwm
)

pico_enable_stdio_usb(test_bldc 1)
pico_enable_stdio_uart(test_bldc 0)

pico_add_extra_outputs(test_bldc)

cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(test_L298N)

pico_sdk_init()

add_executable(test_L298N
    src/L298N.cpp
    src/main.cpp
)

target_include_directories(test_L298N PUBLIC
    inc
)

target_link_libraries(test_L298N
    pico_stdlib
    hardware_pwm
)

pico_enable_stdio_usb(test_L298N 1)
pico_enable_stdio_uart(test_L298N 0)

pico_add_extra_outputs(test_L298N)

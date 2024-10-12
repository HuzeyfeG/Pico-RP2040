cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(balancer_pid)

pico_sdk_init()

add_executable(balancer_pid
    src/main.cpp
    src/BLDC.cpp
    src/MPU6050.cpp
)

target_include_directories(balancer_pid PUBLIC
    inc
)

target_link_libraries(balancer_pid
    pico_stdlib
    hardware_pwm
    hardware_i2c
)

pico_enable_stdio_usb(balancer_pid 1)
pico_enable_stdio_uart(balancer_pid 0)

pico_add_extra_outputs(balancer_pid)

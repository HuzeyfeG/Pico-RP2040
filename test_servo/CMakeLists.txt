cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(test_servo)

pico_sdk_init()

add_executable(test_servo
    src/SERVO.cpp
    src/main.cpp
)

target_include_directories(test_servo PUBLIC
    inc
)

target_link_libraries(test_servo
    pico_stdlib
    hardware_pwm
)

pico_enable_stdio_usb(test_servo 1)
pico_enable_stdio_uart(test_servo 0)

pico_add_extra_outputs(test_servo)

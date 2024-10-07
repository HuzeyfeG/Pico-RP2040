cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(test_mpu6050)

pico_sdk_init()

add_executable(test_mpu6050
    src/main.cpp
    src/MPU6050.cpp
)

target_include_directories(test_mpu6050 PUBLIC
    inc
)

target_link_libraries(test_mpu6050
    pico_stdlib
    hardware_i2c
)

pico_enable_stdio_usb(test_mpu6050 1)
pico_enable_stdio_uart(test_mpu6050 0)

pico_add_extra_outputs(test_mpu6050)

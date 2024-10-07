#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "MPU6050.h"


MPU6050::MPU6050(i2c_inst_t *i2c_instance, uint16_t scl, uint16_t sda) {
    this->i2c = i2c_instance;
    this->scl_pin = scl;
    this->sda_pin = sda;
}


void MPU6050::init() {
    i2c_init(i2c, 400 * 1000);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_pull_up(scl_pin);
    gpio_pull_up(sda_pin);

    uint8_t data[2];
    // Power management register 1
    data[0] = 0x6B;
    data[1] = 0x00;
    i2c_write_blocking(i2c, addr, data, 2, true);

    // Set accelerometer configuration (optional)
    data[0] = 0x1C;
    data[1] = 0x00; // ±2g (default)
    i2c_write_blocking(i2c, addr, data, 2, true);

    // Set gyroscope configuration (optional)
    data[0] = 0x1B;
    data[1] = 0x00; // ±250 degrees/second (default)
    i2c_write_blocking(i2c, addr, data, 2, true);    
}

AccData MPU6050::get_acc() {
    uint8_t accel[6]; // Store data from the 6 acceleration registers
    int16_t accelX, accelY, accelZ; // Combined 3 axis data
    float f_accelX, f_accelY, f_accelZ; // Float type of acceleration data
    uint8_t val = 0x3B; // Start register address

    i2c_write_blocking(i2c, addr, &val, 1, true);
    i2c_read_blocking(i2c, addr, accel, 6, false);

    accelX = ((accel[0]<<8) | accel[1]);
    accelY = ((accel[2]<<8) | accel[3]);
    accelZ = ((accel[4]<<8) | accel[5]);

    AccData rd;
    rd.ax = accelX / 16384.0;
    rd.ay = accelY / 16384.0;
    rd.az = accelZ / 16384.0;
    return rd;
}

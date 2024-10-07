#ifndef MPU6050_H
#define MPU6050_H


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


struct AccData {
    float ax;
    float ay;
    float az;
};

class MPU6050 {
    private:
        i2c_inst_t *i2c;
        uint16_t scl_pin;
        uint16_t sda_pin;
        int addr = 0x68;
    public:
        MPU6050(i2c_inst_t *i2c_instance, uint16_t scl, uint16_t sda);
        void init();
        AccData get_acc();
};

#endif


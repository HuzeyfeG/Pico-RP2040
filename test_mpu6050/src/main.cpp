#include <stdio.h>
#include "pico/stdlib.h"
#include "MPU6050.h"


#define LED_PIN 25

#define I2C_PORT i2c0
#define SCL_PIN 1
#define SDA_PIN 0


MPU6050 mpu(I2C_PORT, SCL_PIN, SDA_PIN);
AccData acc_values;


int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    mpu.init();

    while (true) {
        acc_values = mpu.get_acc();
        printf("X: %6.2f    Y: %6.2f    Z: %6.2f\n", acc_values.ax, acc_values.ay, acc_values.az);
        sleep_ms(20);
    }

    return 0;
}

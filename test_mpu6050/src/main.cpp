#include <stdio.h>
#include "pico/stdlib.h"
#include "MPU6050.h"


#define LED_PIN 25

//  Define port and pins.
#define I2C_PORT i2c0
#define SCL_PIN 1
#define SDA_PIN 0


//	MPU6050, GyroData and AccData objects.
MPU6050 mpu(I2C_PORT, SCL_PIN, SDA_PIN);
GyroData gyro_values;
AccData acc_values;


int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //	Initialize MPU6050.
    mpu.init();
    sleep_ms(250);

    //	MPU6050 calibration.
	mpu.set_gyro_calibration();

    gpio_put(LED_PIN, true);
    while (true) {
        //  Get gyro data.
		gyro_values = mpu.get_gyro();
		gyro_values.gx -= mpu.rate_calibration_x;
        gyro_values.gy -= mpu.rate_calibration_y;
        gyro_values.gz -= mpu.rate_calibration_z;

        //  Get acc data.
        acc_values = mpu.get_acc();

        //  Print gyro and acc data.
        printf("Gx: %6.2f    Gy: %6.2f    Gz: %6.2f\n", gyro_values.gx, gyro_values.gy, gyro_values.gz);
        printf("Ax: %6.2f    Ay: %6.2f    Az: %6.2f\n", acc_values.ax, acc_values.ay, acc_values.az);
        printf("\n-   -   -   -   -   -   -   -   -   -\n\n");
        sleep_ms(250);
    }
    return 0;
}

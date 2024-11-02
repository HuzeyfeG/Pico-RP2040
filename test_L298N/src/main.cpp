#include <stdio.h>
#include "L298N.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"


//	Define LEDs and L298N pins.
#define led_blue 4
#define led_red 6

#define motor_pwm_pin 8
#define forward_enable_pin 10
#define backward_enable_pin 12

//	Create onject for DC Motor and set duty intervals.
L298N bi_dc_motor(motor_pwm_pin, forward_enable_pin, backward_enable_pin, 250, 500);

int main(){
	stdio_init_all();
	gpio_init(led_blue);
    gpio_init(led_red);
	gpio_set_dir(led_blue, GPIO_OUT);
    gpio_set_dir(led_red, GPIO_OUT);

	while (true){
		//  Write the duty to the DC Motor.
        for(int i = 250; i <= 500; i++) {
            bi_dc_motor.motor_forward(i);
            gpio_put(led_blue, 1);
            gpio_put(led_red, 0);
            sleep_ms(10);
        }
        gpio_put(led_blue, 0);
        gpio_put(led_red, 0);
        bi_dc_motor.motor_stop();
        sleep_ms(2000);
        for(int i = 500; i >= 250; i--) {
        bi_dc_motor.motor_backward(i);
            gpio_put(led_blue, 0);
            gpio_put(led_red, 1);
            sleep_ms(10);
        }
        gpio_put(led_blue, 0);
        gpio_put(led_red, 0);
        bi_dc_motor.motor_brake();
        sleep_ms(2000);

	}
}


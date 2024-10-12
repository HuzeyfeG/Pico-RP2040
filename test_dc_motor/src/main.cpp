#include <stdio.h>
#include "DC_MOTOR.h"


//	Define LED and DC Motor pins.
#define led 25
#define dc_motor_pin 2

//	Create onject for DC Motor and set duty intervals.
DC_MOTOR dc_motor(dc_motor_pin, 0, 33);


int main(){
	stdio_init_all();
	gpio_init(led);
	gpio_set_dir(led, GPIO_OUT);
	gpio_put(led, true);

    dc_motor.set_duty(0.0);
    sleep_ms(5000);

	while (true){
		//	Write the duty to the DC Motor.
        for(float i = 0; i <= 33; i++) {
            dc_motor.set_duty(i);
            sleep_ms(300);
        }
		sleep_ms(2000);
        for(float i = 33; i >= 0; i--) {
            dc_motor.set_duty(i);
            sleep_ms(300);
        }
		sleep_ms(5000);
	}
}


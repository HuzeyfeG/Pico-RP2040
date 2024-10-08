#include <stdio.h>
#include "SERVO.h"


#define servo_pin 2


int main(){
	stdio_init_all();

	Servo servo(servo_pin, 600, 2500);
    servo.set_degree(0.0);
    sleep_ms(1000);

	while (true){
		servo.set_degree(60.0);
		sleep_ms(2000);
		servo.set_degree(120.0);
		sleep_ms(2000);
		servo.set_degree(180.0);
		sleep_ms(2000);
		servo.set_degree(120.0);
		sleep_ms(2000);
        servo.set_degree(60.0);
		sleep_ms(2000);
		servo.set_degree(0.0);
		sleep_ms(2000);

        for(float i = 0.0; i <= 180.0; i++) {
            servo.set_degree(i);
            sleep_ms(10);
        }
		sleep_ms(2000);
        for(float i = 180.0; i >= 0.0; i--) {
            servo.set_degree(i);
            sleep_ms(10);
        }
		sleep_ms(2000);
	}
}


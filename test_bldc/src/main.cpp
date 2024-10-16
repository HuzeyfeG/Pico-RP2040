#include <stdio.h>
#include "BLDC.h"

//	Define BLDC pin.
#define BLDC_PIN 4


int main(){
	stdio_init_all();

	//	Set the pin number and duty interval.
	BLDC bldc(BLDC_PIN, 1000, 2000);
    bldc.set_power(0.0);
    sleep_ms(5000);

	while (true){
		//	Let the party begin!
		bldc.set_power(10.0);
   		sleep_ms(2000);
		bldc.set_power(20.0);
   		sleep_ms(2000);
		bldc.set_power(30.0);
   		sleep_ms(2000);
		bldc.set_power(20.0);
   		sleep_ms(2000);
		bldc.set_power(10.0);
   		sleep_ms(2000);
		bldc.set_power(0.0);
   		sleep_ms(2000);

        for(float i = 0.0; i <= 30.0; i++) {
            bldc.set_power(i);
            sleep_ms(200);
        }
        for(float i = 30.0; i >= 0.0; i--) {
            bldc.set_power(i);
            sleep_ms(200);
        }
		sleep_ms(5000);
	}
}

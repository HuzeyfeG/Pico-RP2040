#include <stdio.h>
#include "hardware/adc.h"
#include "BLDC.h"


#define bldc_pin 2

uint16_t pot_value;

//	Type the impulse that you want to. 1000 - 2000 in this case.
BLDC bldc(bldc_pin, 1000, 2000);

//	Map the data from the pot. (Optional)
uint8_t map(int x, int in_min, int in_max, int out_min, int out_max);

int main(){
	stdio_init_all();
	adc_init();
	
	gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
	gpio_put(25, true);

	//	Define adc pin and set as input.
	adc_gpio_init(26);
	adc_select_input(0);

	while (true){
		//	Read data from pot.
		pot_value = adc_read();
		//	Limit the data. (Optional)
		if (pot_value <= 1000) {
			pot_value = 1000;
		} else if(pot_value >= 3000) {
			pot_value = 3000;
		}
		pot_value = map(pot_value, 1000, 3000, 0, 100);
		// printf("Pot: %d\n", pot_value);
		// sleep_ms(100);

		// For calibration, first set full duty while esc has no power. Connect the power. 
		// After beep sound immediately make it zero. You hear couple beeps, it means Ok. 
		bldc.set_power(pot_value);
	}
}

//	Mapping equation.
uint8_t map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
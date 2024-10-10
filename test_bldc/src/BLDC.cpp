#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "BLDC.h"


BLDC::BLDC(uint8_t gp, uint16_t min_duty, uint16_t max_duty) {
	this->p_gp = gp;
	this->min_duty = min_duty;
	this->max_duty = max_duty;

	gpio_init(gp);
	gpio_set_function(gp, GPIO_FUNC_PWM);
	pwm_set_gpio_level(gp, 0);
	
	//	Get the slice number of the pin.
	uint slice_num = pwm_gpio_to_slice_num(gp);

	//	Set the frequency to 50Hz.
	uint32_t clk = clock_get_hz(clk_sys);
	uint32_t div = clk / (20000 * 50);
	pwm_set_clkdiv(slice_num, div);

	// Set the wrap to 20000.
	pwm_set_wrap(slice_num, 20000);

	//	Enable pwm.
	pwm_set_enabled(slice_num, true);
}


void BLDC::set_power(float power){
	if(power >= 100.0){
		power = 100.0;
	} else if(power <= 0.0){
		power = 0.0;
	}
	
	//	Convert the data between max and min duty.
	int duty = (((float)(max_duty - min_duty) / 100.0) * power) + min_duty;
	pwm_set_gpio_level(p_gp, duty);
}








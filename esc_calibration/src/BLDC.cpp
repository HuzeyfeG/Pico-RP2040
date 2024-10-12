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
	this->slice_num = pwm_gpio_to_slice_num(gp);
	
	//	Set the frequency to 50Hz. Formula: (Clock / Divider) / Wrap -> (125MHz / 125) / 20000 = 50Hz.
	pwm_set_clkdiv(this->slice_num, 125.0);
	
	// Set the wrap to 20000.
	pwm_set_wrap(this->slice_num, 20000);
}


void BLDC::set_power(float power){
	if(power >= 100.0){
		power = 100.0;
	} else if(power <= 0.0){
		power = 0.0;
	}
	
	//	Convert the data between max and min duty.
	int duty = (((float)(max_duty - min_duty) / 100.0) * power) + min_duty;
	pwm_set_chan_level(this->slice_num, PWM_CHAN_A, duty);
	//	Enable pwm.
	pwm_set_enabled(this->slice_num, true);
}








#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "DC_MOTOR.h"


DC_MOTOR::DC_MOTOR(uint8_t gp, uint16_t min_duty, uint16_t max_duty){
	this->p_gp = gp;
	this->min_duty = min_duty;
	this->max_duty = max_duty;

	gpio_init(gp);
	gpio_set_function(gp, GPIO_FUNC_PWM);
	pwm_set_gpio_level(gp, 0);
	
	//	Get the slice number of the pin.
	this->slice_number = pwm_gpio_to_slice_num(gp);

	//	Set the frequency to 30KHz. Formula: (Clock / Divider) / Wrap -> (125MHz / 125) / 33 = 30KHz.
	pwm_set_clkdiv(this->slice_number, 125);

	// Set the wrap to 33.
	pwm_set_wrap(this->slice_number, 33);
}


void DC_MOTOR::set_duty(int duty){
	if(duty >= 33){
		duty = 33;
	} else if(duty <= 0){
		duty = 0;
	}
	//	Go! Go! Go!
	pwm_set_chan_level(this->slice_number, PWM_CHAN_A, duty);
	pwm_set_enabled(this->slice_number, true);
}
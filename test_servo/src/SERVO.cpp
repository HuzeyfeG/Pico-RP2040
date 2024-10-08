#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "SERVO.h"


Servo::Servo(uint8_t gp, uint16_t min_duty, uint16_t max_duty){
	this->p_gp = gp;
	this->min_duty = min_duty;
	this->max_duty = max_duty;

	gpio_init(gp);
	gpio_set_function(gp, GPIO_FUNC_PWM);
	pwm_set_gpio_level(gp, 0);
	
	uint slice_num = pwm_gpio_to_slice_num(gp);

	uint32_t clk = clock_get_hz(clk_sys);
	uint32_t div = clk / (20000 * 50);
	pwm_set_clkdiv(slice_num, div);

	pwm_set_wrap(slice_num, 20000);

	pwm_set_enabled(slice_num, true);
}


void Servo::set_degree(float degree){
	if(degree >= 180.0){
		degree = 180.0;
	} else if(degree <= 0.0){
		degree = 0.0;
	}
	
	int duty = (((float)(max_duty - min_duty) / 180.0) * degree) + min_duty;
	pwm_set_gpio_level(p_gp, duty);
}
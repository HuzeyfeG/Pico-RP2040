#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "L298N.h"


L298N::L298N(uint8_t motor_pwm_pin, uint8_t forward_enable_pin, uint8_t backward_enable_pin, uint16_t min_duty, uint16_t max_duty) {
	this->motor_pwm_pin = motor_pwm_pin;
	this->forward_enable_pin = forward_enable_pin;
	this->backward_enable_pin = backward_enable_pin;
	this->max_duty = max_duty;
	this->min_duty = min_duty;

	gpio_init(this->motor_pwm_pin);
	gpio_set_function(this->motor_pwm_pin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(this->motor_pwm_pin, 0);

	gpio_init(this->forward_enable_pin);
	gpio_init(this->backward_enable_pin);
	gpio_set_dir(this->forward_enable_pin, GPIO_OUT);
	gpio_set_dir(this->backward_enable_pin, GPIO_OUT);

	//	Get the slice number of the pin.
	this->slice_motor_pwm_pin = pwm_gpio_to_slice_num(this->motor_pwm_pin);

	//	Set the frequency to 2KHz. Formula: (Clock / Divider) / Wrap -> (125MHz / 125) / 500 = 2KHz.
	pwm_set_clkdiv(this->slice_motor_pwm_pin, 125);

	// Set the wrap to 500.
	pwm_set_wrap(this->slice_motor_pwm_pin, 500);
}


void L298N::motor_forward(int duty) {
	if(duty >= this->max_duty){
		duty = this->max_duty;
	} else if(duty <= this->min_duty){
		duty = this->min_duty;
	}
	//	Go! Go! Go!

	gpio_put(this->forward_enable_pin, 1);
	gpio_put(this->backward_enable_pin, 0);

	pwm_set_chan_level(this->slice_motor_pwm_pin, PWM_CHAN_A, duty);

	pwm_set_enabled(this->slice_motor_pwm_pin, true);
}

void L298N::motor_backward(int duty) {
	if(duty >= this->max_duty){
		duty = this->max_duty;
	} else if(duty <= this->min_duty){
		duty = this->min_duty;
	}
	//	Go! Go! Go!

	gpio_put(this->forward_enable_pin, 0);
	gpio_put(this->backward_enable_pin, 1);

	pwm_set_chan_level(this->slice_motor_pwm_pin, PWM_CHAN_A, duty);

	pwm_set_enabled(this->slice_motor_pwm_pin, true);
}

void L298N::motor_brake() {
	gpio_put(this->forward_enable_pin, 1);
	gpio_put(this->backward_enable_pin, 0);

	pwm_set_chan_level(this->slice_motor_pwm_pin, PWM_CHAN_A, 0);

	pwm_set_enabled(this->slice_motor_pwm_pin, true);
}

void L298N::motor_stop() {
	gpio_put(this->forward_enable_pin, 0);
	gpio_put(this->backward_enable_pin, 0);
}
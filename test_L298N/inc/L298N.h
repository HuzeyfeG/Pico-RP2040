#ifndef L298N_H
#define L298N_H

#include "pico/stdlib.h"

class L298N {
	public:
		//	General variables and functions.
		uint8_t motor_pwm_pin, forward_enable_pin, backward_enable_pin;
		uint16_t min_duty, max_duty;
		uint slice_motor_pwm_pin;

		L298N(uint8_t motor_pwm_pin, uint8_t forward_enable_pin, uint8_t backward_enable_pin, uint16_t min_duty, uint16_t max_duty);
		void motor_forward(int duty);
		void motor_backward(int duty);
		void motor_brake();
		void motor_stop();
};


#endif
#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

class Servo {
	public:
		//	General variables and functions
		uint8_t p_gp;
		uint16_t min_duty, max_duty;

		Servo(uint8_t gp, uint16_t min_duty, uint16_t max_duty);
		void set_degree(float degree);
};


#endif
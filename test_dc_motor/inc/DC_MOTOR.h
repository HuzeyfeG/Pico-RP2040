#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "pico/stdlib.h"

class DC_MOTOR {
	public:
		//	General variables and functions.
		uint8_t p_gp;
		uint16_t min_duty, max_duty;
		uint slice_number;

		DC_MOTOR(uint8_t gp, uint16_t min_duty, uint16_t max_duty);
		void set_duty(int duty);
};


#endif
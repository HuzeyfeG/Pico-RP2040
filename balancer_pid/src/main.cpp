#include <stdio.h>
#include "BLDC.h"
#include "MPU6050.h"


//	Define pin for internal LED.
#define LED_PIN 25

//	Define protocol and pins for the MPU6050.
#define I2C_PORT i2c0
#define SCL_PIN 1
#define SDA_PIN 0

//	Define pins for the BLDCs.
#define bldc_l_PIN 2
#define bldc_r_PIN 4


//	Create objects for MPU6050 and data.
MPU6050 mpu(I2C_PORT, SCL_PIN, SDA_PIN);
AccData acc_values;

//	Create onjects for BLDCs and set duty intervals.
BLDC bldc_l(bldc_l_PIN, 1000, 2000);
BLDC bldc_r(bldc_r_PIN, 1000, 2000);


//	PID constants ve variables.
//	Note: Kp, Ki and Kd constants can be different in every systems.
float Kp = 55.0, Ki = 1.0, Kd = 0.5;
float input_throttle = 5.0, desired_rate_roll = 0.0, pid_return[] = {0, 0, 0};
float input_roll, error_rate_roll, prev_error_rate_roll, prev_iterm_rate_roll;
void pid_equation(float error, float kp, float ki, float kd, float prev_error, float prev_iterm);


int main(){
	stdio_init_all();
	gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

	//	Initialize MPU6050 and BLDCs.
	mpu.init();
    bldc_l.set_duty(1000);
	bldc_r.set_duty(1000);
    sleep_ms(5000);

	gpio_put(LED_PIN, true);
	while (true){
		//  Get acc data.
        acc_values = mpu.get_acc();
		
		//	Convert the input throttle power between max and min duty.
		int duty_l = bldc_l.power_to_duty(input_throttle);
		int duty_r = bldc_r.power_to_duty(input_throttle);

		//	PID controller.
		error_rate_roll = desired_rate_roll - acc_values.ay;
		pid_equation(error_rate_roll, Kp, Ki, Kd, prev_error_rate_roll, prev_iterm_rate_roll);
		input_roll = pid_return[0];
		prev_error_rate_roll = pid_return[1];
		prev_iterm_rate_roll = pid_return[2];

		//	Calculate the BLDCs outputs.
		duty_l -= input_roll;
		duty_r += input_roll;

		//	Limit the duty of BLDCs.
		if(duty_l > 1200) {
			duty_l = 1200;
		}
		if (duty_r > 1200) {
			duty_r = 1200;
		}

		//	Write the duty to the BLDCs.
		bldc_l.set_duty(duty_l);
		bldc_r.set_duty(duty_r);
	}
}


//	PID equation
void pid_equation(float error, float kp, float ki, float kd, float prev_error, float prev_iterm) {
	//	Calculate the P.
	float p_term = kp * error;

	//	Calculate the I.
	float i_term = prev_iterm + (ki * (error + prev_error) * 0.004 / 2);
	if(i_term > 400) {
		i_term = 400;
	} else if(i_term < -400) {
		i_term = -400;
	}

	//	Calculate the D.
	float d_term = kd * ((error - prev_error) / 0.004);

	//	P+I+D
	float pid_output = p_term + i_term + d_term;
	if(pid_output > 400) {
		pid_output = 400;
	} else if(pid_output < -400) {
		pid_output = -400;
	}

	//	Transfer results to variable.
	pid_return[0] = pid_output;
	pid_return[1] = error;
	pid_return[2] = i_term;
}

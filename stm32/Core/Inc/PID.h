/*
 * PID.h
 *
 *  Created on: 14 mar 2026
 *      Author: arkadiuszromanczuk
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>

typedef struct {
	float Kp; // Proportional gain
	float Ki; // integrating gain
	float Kd; // differentiating gain

	float setpoint; //set-point
	float intergral; //error integral
	float prev_error; //previous error

	float out_min; //min initial value
	float out_max; //max initial value

	float integral_limits; //limit of an integral
	float sample_time; //trial period

} PID_t;

void PID_Init(PID_t *pid, float Kp, float Ki, float Kd, float sample_time, float out_min, float out_max);

void PID_SetSetPoint(PID_t *pid, float setpoint);

void PID_Reset(PID_t *pid);

float PID_Compute(PID_t *pid, float input);


#endif /* INC_PID_H_ */

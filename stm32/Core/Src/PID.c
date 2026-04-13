/*
 * PID.c
 *
 *  Created on: 14 mar 2026
 *      Author: arkadiuszromanczuk
 */

#include "PID.h"

void PID_Init(PID_t *pid, float Kp, float Ki, float Kd, float sample_time, float out_min, float out_max)
	{
		pid->Kp = Kp;
		pid->Ki = Ki;
		pid->Kd = Kd;
		pid->sample_time =sample_time;
		pid->out_min = out_min;
		pid->out_max = out_max;

		pid->integral_limits = (out_max - out_min);

	};

void PID_SetSetPoint(PID_t *pid, float setpoint)
	{
		pid->setpoint = setpoint;
	};

void PID_Reset(PID_t *pid)
	{
		pid->intergral = 0.0f;
		pid->prev_error = 0.0f;
	};

float PID_Compute(PID_t *pid, float input)
	{
		//error
		float error = pid->setpoint - input;
		//proportional
		float Pout = pid->Kp *error;

		pid->intergral += error * pid->sample_time;

		if(pid->intergral > pid->integral_limits)
			pid->intergral = pid->integral_limits;

		else if(pid->intergral < -pid->integral_limits)
			pid->intergral = -pid->integral_limits;

		float Iout = pid->Ki * pid->intergral;
		//differentiating
		float derivative = (error - pid->prev_error) / pid->sample_time;
		float Dout = pid->Kd * derivative;
		//pid out
		float output = Pout + Iout + Dout;
		//output limit
		if(output > pid->out_max)
			output = pid->out_max;
		else if(output < pid->out_min)
			output = pid->out_min;
		//keep error for next step
		pid->prev_error = error;

		return output;

	};












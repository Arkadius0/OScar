#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
//#include "stdint.h"
//#include "stm32f1xx_hal.h"
//#include "stm32f1xx_ll_tim.h"

typedef struct {
    TIM_HandleTypeDef *htim; // Timer handle for PWM
    uint32_t channel; // Timer channel for PWM
    GPIO_TypeDef *dir_port1; // GPIO port for direction pin 1
    uint16_t dir_pin1_num; // GPIO pin number for direction pin 1
    GPIO_TypeDef *dir_port2; // GPIO port for direction pin 2
    uint16_t dir_pin2_num; // GPIO pin number for direction pin 2
} MOTOR_t;

void Motor_Init(MOTOR_t *motor);
void Motor_SetSpeed(MOTOR_t *motor, int16_t speed);
void Motor_Stop(MOTOR_t *motor);

#endif // MOTOR_H

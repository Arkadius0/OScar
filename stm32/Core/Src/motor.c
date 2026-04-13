
#include "motor.h"

void Motor_Init(MOTOR_t* motor) {
    HAL_TIM_PWM_Start(motor->htim, motor->channel); // Start PWM on the specified timer and channel
}

void Motor_SetSpeed(MOTOR_t* motor, int16_t speed) {
    if(speed > 1000) speed = 1000; // Cap speed to 100%
    if(speed < -1000) speed = -1000; // Cap speed to -100%
    // Set the motor speed and direction based on the speed value
    // This is a placeholder; actual implementation will depend on your hardware setup
    if (speed > 0) {
        HAL_GPIO_WritePin(motor->dir_port1, motor->dir_pin1_num, GPIO_PIN_SET); // Set IN1 high
        HAL_GPIO_WritePin(motor->dir_port2, motor->dir_pin2_num, GPIO_PIN_RESET); // Set IN2 low
        // Set PWM duty cycle based on speed
    } else if (speed < 0) {
        // Set IN1 low and IN2 high for reverse direction
        HAL_GPIO_WritePin(motor->dir_port1, motor->dir_pin1_num, GPIO_PIN_RESET); // Set IN1 low
        HAL_GPIO_WritePin(motor->dir_port2, motor->dir_pin2_num, GPIO_PIN_SET); // Set IN2 high
        // Set PWM duty cycle based on speed
    } else {
        // Stop the motor
        Motor_Stop(motor);
    }
    uint32_t pwm = speed > 0 ? speed : -speed;
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel, pwm); // Set PWM duty cycle based on absolute speed value
}

void Motor_Stop(MOTOR_t* motor) {
    // Set both IN1 and IN2 low to stop the motor
     HAL_GPIO_WritePin(motor->dir_port1, motor->dir_pin1_num, GPIO_PIN_RESET); // Set IN1 low
     HAL_GPIO_WritePin(motor->dir_port2, motor->dir_pin2_num, GPIO_PIN_RESET); // Set IN2 low
}

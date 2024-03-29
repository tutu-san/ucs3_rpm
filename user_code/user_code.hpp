#pragma once
#ifndef USER_CODE_HPP
#define USER_CODE_HPP
//includes
#include <main.h>
#include <cstdint>
#include "stm32f4xx_hal.h"
#include "lib/pi_ctrl.hpp"
#include "lib/encoder.hpp"
#include "lib/motor.hpp"

//(extern) variables, classes
extern CAN_HandleTypeDef hcan1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim5;

extern uint32_t can1_rx_id;
extern uint8_t can1_rx_data[8];

extern encoder_tool encoders_amt_102[4];
extern pid_control pid [4];
extern motor_rotation motors[4];

extern float motor_pwm[4];

//functions
void setup();
void loop();

void can_setup();
void can1_receive_process();

int pcdata_to_rpm(uint8_t, uint8_t);

void pwm_setup();
void encoder_setup();
void motor_brake_off();

#endif

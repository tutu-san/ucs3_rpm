#pragma once
#ifndef USER_CODE_HPP
#define USER_CODE_HPP
//includes
#include <cstdint>
#include "stm32f4xx_hal.h"
#include "lib/pi_ctrl.hpp"
#include "lib/encoder.hpp"
#include "lib/motor.hpp"

//(extern) variables, classes
extern CAN_HandleTypeDef hcan1;

extern uint32_t can1_rx_id;
extern uint8_t can1_rx_data[8];

extern encoder_tool encoders_amt_102[4];
extern pid_control pid [4];
extern motor_rotation motors[4];

//functions
void setup();
void loop();

void can_setup();
void can1_receive_process();

int pcdata_to_rpm(uint8_t, uint8_t);

#endif

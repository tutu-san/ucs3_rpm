/**
 * @file motor.hpp
 * @brief 実際にモーターを回す指示をする
 * @author tutu-san
 */
#pragma once

#ifndef MOTOR_HPP
#define MOTOR_HPP

//includes
#include "stm32f4xx_hal.h"
#include <cmath>


class motor_rotation{
private:
	GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
	TIM_HandleTypeDef* tim_handle;
	uint32_t tim_channel;
	bool motor_exception;
	void clamp(float&, float, float);
public:
    motor_rotation(GPIO_TypeDef* _gpio_port, uint16_t _gpio_pin, TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel, bool _motor_exception)
    	:gpio_port(_gpio_port),gpio_pin(_gpio_pin),tim_handle(_tim_handle), tim_channel(_tim_channel), motor_exception(_motor_exception){}
    void rotate(float);
};
#endif

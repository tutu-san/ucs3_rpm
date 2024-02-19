#include "motor.hpp"
#include <algorithm>

//回転指令
void motor_rotation::rotate(float motor_pwm){
	//motor_pwmのクランプ
	motor_rotation::clamp(motor_pwm, -65535.0f, 65535.0f);
	//モーターの回転方向をエンコーダーが暴走しないようにする
	if(this->motor_exception == true){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_RESET : GPIO_PIN_SET));
	}else{
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_SET : GPIO_PIN_RESET));
	}
	//PWM出力を更新する
	__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm));
}

//std::clampちゃんが起きないので
void motor_rotation::clamp(float&terget_variable , float min, float max){
    if(terget_variable < min){
        terget_variable = min;
        return;
    }else if(terget_variable > max){
        terget_variable = max;
        return;
    }else{
        return;
    }
}

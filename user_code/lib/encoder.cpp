#include "encoder.hpp"

int16_t encoder_tool::read_step(){
    // enc_debug = __HAL_TIM_GET_COUNTER(this->tim_handle); //エンコーダーの故障確認用
    return  __HAL_TIM_GET_COUNTER(this->tim_handle);
}

void encoder_tool::reset_encoder_data(){
    __HAL_TIM_SET_COUNTER(this->tim_handle, 0);
}

int16_t encoder_tool::read_rad_per_sec(){
    int16_t step_data = 0;
    step_data = read_step();
    return step_data * step_to_rad_per_sec_constant;
}

int16_t encoder_tool::read_rpm(){
    int16_t rad_per_sec_data = 0;
    rad_per_sec_data = read_rad_per_sec();
    return rad_per_sec_data * rad_per_sec_to_rpm_constant;
}

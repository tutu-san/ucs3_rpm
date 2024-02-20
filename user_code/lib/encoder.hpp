/**
 * @file encoder.hpp
 * @brief エンコーダー(amt-102)からステップ読み取り & rpm(ロボマスc610/620互換)への変換
 * @author tutu-san
 */

#pragma once

#ifndef encoder_HPP
#define encoder_HPP

//includes
#include "stm32f4xx_hal.h" // stm32の使用するチップよって変わる
#include <cmath>
#include <cstdint>
//encoder
class encoder_tool{
private:
    TIM_HandleTypeDef* tim_handle;
    const float resolution; //エンコーダーのPPRに当たるもの
    const float gear_ratio; //モーターのギア比？
    constexpr static float DELTA_T = 0.01f; //単位はsec
    float step_to_rad_per_sec_constant;
    constexpr static float rad_per_sec_to_rpm_constant = 60.0f / (2.0f * M_PI);
//    int16_t enc_debug = 0; //ステップ読み取り値 cube monitor確認用
    int16_t enc_rpm_debug = 0;
public:
    encoder_tool(TIM_HandleTypeDef* _tim_handle, float _resolution, float _gear_ratio)
    :tim_handle(_tim_handle),resolution(_resolution), gear_ratio(_gear_ratio){
        step_to_rad_per_sec_constant = (2 * M_PI) / (4 * resolution * DELTA_T);
    }
    int16_t read_step();
    int16_t read_rad_per_sec();
    int16_t read_rpm();
    void reset_encoder_data();
};
#endif

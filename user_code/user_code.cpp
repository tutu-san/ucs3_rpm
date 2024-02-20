#include "user_code.hpp"
/*main_functions*/
void setup(){
    can_setup();
    pwm_setup();
    encoder_setup();
}

void loop(){
    for(int i=0; i<4; i++){
        float motor_pwm[4] = {0,0,0,0};
        motor_pwm[i] = pid[i].motor_calc(encoders_amt_102[i].read_rpm());
        motors[i].rotate(motor_pwm[i]);
        encoders_amt_102[i].reset_encoder_data();
    }
}

/*can_functions*/
void can_setup(){
//CAN1
    CAN_FilterTypeDef filter;
    filter.FilterIdHigh = 0;      // フィルターID(上位16ビット)
    filter.FilterIdLow = 0;       // フィルターID(下位16ビット)
    filter.FilterMaskIdHigh = 0;  // フィルターマスク(上位16ビット)
    filter.FilterMaskIdLow = 0;   // フィルターマスク(下位16ビット)
    filter.FilterScale = CAN_FILTERSCALE_32BIT;  // フィルタースケール
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;   // フィルターに割り当てるFIFO
    filter.FilterBank = 0;  // フィルターバンクNo
    filter.FilterMode = CAN_FILTERMODE_IDMASK;  // フィルターモード
    filter.SlaveStartFilterBank = 14;  // スレーブCANの開始フィルターバンクNo
    filter.FilterActivation = ENABLE;  // フィルター無効／有効
    HAL_CAN_ConfigFilter(&hcan1, &filter);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void can1_receive_process(){
    //from pc
    if(can1_rx_id == 0x300){
    	int rpm_data_from_pc[4] = {0,0,0,0};
    	rpm_data_from_pc[0] = pcdata_to_rpm(can1_rx_data[0], can1_rx_data[1]);
    	rpm_data_from_pc[1] = pcdata_to_rpm(can1_rx_data[2], can1_rx_data[3]);
    	rpm_data_from_pc[2] = pcdata_to_rpm(can1_rx_data[4], can1_rx_data[5]);
    	rpm_data_from_pc[3] = pcdata_to_rpm(can1_rx_data[5], can1_rx_data[6]);
        for(int i=0; i<4; i++){
        	pid[i].update_target_speed((float)rpm_data_from_pc[i]);
        }
    }
}

int pcdata_to_rpm(uint8_t pc_input_data_high, uint8_t pc_input_data_low){
    //上位,下位ビットの統合
    uint16_t unsigned_rpm_data = pc_input_data_high << 8 | pc_input_data_low;
    int16_t signed_rpm_data = 0;

    signed_rpm_data = unsigned_rpm_data;

    //おしまい
    return signed_rpm_data;
}

/*timer_setup*/
void pwm_setup(){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
}

void encoder_setup(){
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);

}

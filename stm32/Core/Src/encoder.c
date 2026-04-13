#include "encoder.h"


void Encoder_Init(ENCODER_t *enc)
{
    HAL_TIM_Encoder_Start(enc->htim, TIM_CHANNEL_ALL);
}

int32_t Encoder_GetTicks(ENCODER_t *enc)
{
    return (int32_t)__HAL_TIM_GET_COUNTER(enc->htim);
}

void Encoder_Reset(ENCODER_t *enc)
{
    __HAL_TIM_SET_COUNTER(enc->htim, 0);
}

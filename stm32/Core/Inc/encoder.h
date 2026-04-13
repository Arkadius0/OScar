
#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"

typedef struct
{
    TIM_HandleTypeDef *htim;

} ENCODER_t;

void Encoder_Init(ENCODER_t *enc);
int32_t Encoder_GetTicks(ENCODER_t *enc);
void Encoder_Reset(ENCODER_t *enc);

#endif

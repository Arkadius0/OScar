/*
 * spi_slave.h
 *
 *  Created on: 14 mar 2026
 *      Author: arkadiuszromanczuk
 */

#ifndef INC_SPI_SLAVE_H_
#define INC_SPI_SLAVE_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

typedef void (*SPI_Slave_Callback_t)(uint8_t data); //Recives bytes data

void SPI_Slave_Init(SPI_HandleTypeDef *hspi, SPI_Slave_Callback_t callback); //initialize SPI Slave

void SPI_Slave_IRQHandler(SPI_HandleTypeDef *hspi); //hspi A pointer to the SPI handle structure.


#endif /* INC_SPI_SLAVE_H_ */

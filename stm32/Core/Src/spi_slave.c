/*
 * spi_slave.c
 *
 *  Created on: 14 mar 2026
 *      Author: arkadiuszromanczuk
 */

#include "spi_slave.h"

//A sturcture that stores the library's state
typedef struct
	{
	SPI_HandleTypeDef *hspi; //Pointer for handle SPI
	SPI_Slave_Callback_t user_callback; //User callback function
	uint8_t rx_buffer; //Buffer for recived bytes
	uint8_t initialized; //Initialization flag
	}SPI_Slave_State_t;

static SPI_Slave_State_t spi_state = {0};

void SPI_Slave_Init(SPI_HandleTypeDef *hspi, SPI_Slave_Callback_t callback)
	{
	//save pointer and callback
	spi_state.hspi = hspi;
	spi_state.user_callback = callback;
	spi_state.initialized =1;
	//clear buffer
	spi_state.rx_buffer = 0;
	//start receiving
	HAL_SPI_Receive_IT(spi_state.hspi, &spi_state.rx_buffer, 1);
	}

void SPI_Slave_IRQHandler(SPI_HandleTypeDef *hspi)
	{
	//Check whether the interrupt is coming from our SPI
	if(hspi->Instance == spi_state.hspi->Instance)
	{
		//Call the user's callback with the received byte
		if(spi_state.user_callback != NULL)
		{
			spi_state.user_callback(spi_state.rx_buffer);
		}
		//Start receiving the next byte
		HAL_SPI_Receive_IT(spi_state.hspi, &spi_state.rx_buffer, 1);

	}
	}






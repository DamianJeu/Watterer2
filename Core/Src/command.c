/*
 * command.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Damia
 */

#include "command.h"

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "string.h"
#include "stm32f1xx_hal_def.h"

#define UART_INSTANCE huart1

uint8_t uartBuffer[UART_BUF_SIZE];
uint8_t uartSingle;

void (*func)(uint8_t *msg);

void Register_MsgComplited_Callback(void (*funcTmp)(uint8_t *msg))
{

	func = funcTmp;

}

void Communication_Init(void)
{

	HAL_UART_Receive_IT(&UART_INSTANCE, &uartSingle, 1);

}

void Send_Uart_Msg(uint8_t *msg, uint8_t len)
{

	HAL_UART_Transmit_IT(&UART_INSTANCE, (uint8_t*) msg, len);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t cnt;

	if (huart->Instance == USART1)
	{
		HAL_UART_Receive_IT(&UART_INSTANCE, &uartSingle, 1);
		uartBuffer[cnt]=uartSingle;
		cnt++;

		if (cnt == 4)
		{


			if (func)
				func(uartBuffer);
			HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
			cnt=0;

		}

	}

}

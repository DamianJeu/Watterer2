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
uint8_t uartChar;

void (*func)(uint8_t *msg, size_t len);

void Register_MsgComplited_Callback(void (*funcTmp)(uint8_t *msg, size_t len)) {

	func = funcTmp;

}

void Communication_Init(void) {

	HAL_UART_Receive_IT(&UART_INSTANCE, &uartChar, 1);

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {

	if (huart->Instance == USART1) {

		UNUSED(huart);
	}

}

void Send_Uart_Msg(char * msg)
{

	uint16_t len;

	len=strlen(msg);

	HAL_UART_Transmit_IT(&UART_INSTANCE, (uint8_t*) msg, len);


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	static uint8_t bufCnt;

	if (huart->Instance == USART1) {
		//single chars from message
		if (uartChar != '\n') {

			if (bufCnt > UART_BUF_SIZE) {
				bufCnt = 0;

			} else {
				uartBuffer[bufCnt++] = uartChar;
			}

		} else if (uartChar == '\n') //complite message
				{

			uartBuffer[bufCnt] = 0;
			if (func != NULL) {
				func(uartBuffer, strlen((char*) uartBuffer));
			}
			HAL_UART_Transmit_IT(&UART_INSTANCE, (uint8_t*) "OK!", 4);

		}

		HAL_UART_Receive_IT(&UART_INSTANCE, &uartChar, 1);

	}

}

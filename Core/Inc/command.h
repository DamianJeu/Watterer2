/*
 * command.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Damia
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#define  UART_BUF_SIZE 4

#include "main.h"



void Communication_Init(void);
void Register_MsgComplited_Callback(void (*funcTmp)(uint8_t *msg));
void Send_Uart_Msg(uint8_t * msg, uint8_t len);



#endif /* COMMAND_H_ */

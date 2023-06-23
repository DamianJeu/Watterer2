/*
 * command.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Damia
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#define  UART_BUF_SIZE 20

#include "main.h"



void Communication_Init(void);
void Register_MsgComplited_Callback(void (*funcTmp)(uint8_t *msg, size_t len));
void Send_Uart_Msg(char * msg);



#endif /* COMMAND_H_ */

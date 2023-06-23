/*
 * communication.c
 *
 *  Created on: 22 cze 2023
 *      Author: djeutner
 */
#include <stdlib.h>

#include "main.h"
#include "communication.h"
#include "command.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal_def.h"

char commandBuffer1[] = "Higro,Temp,HigroST";
char commandBuffer2[] = "CH1,CH2";
char commandBuffer3[] = "?";

typedef enum
{
	Error = -1, Higro, Temp, HigroST

} First_Message_E;

typedef enum
{
	CH1, CH2
} Second_Message_E;

typedef enum
{
	REQ

} Third_Message_E;

/*************FRAME*************/
/******* COMMAND_CHANEL ********/

uint8_t Check_Command(char *command, char *buffer)
{
	char *token;
	uint8_t index = 0;

	token = strtok(buffer, ",");

	if (!strcmp(token, command))
	{
		return 0;
	}

	while (token != NULL)
	{
		token = strtok(NULL, ",");
		index++;
		if (!strcmp(token, command))
		{
			return index;
		}

	}
	//command not recognized
	return -1;
}

void Command_Handling(First_Message_E firstMsg, Second_Message_E secondMsg,
		Third_Message_E thirdMsg)
{

	if (firstMsg == Higro)
	{
		if (secondMsg == CH1)
		{
			Send_Uart_Msg("CH1_VALUE_H");
		}
		else if (secondMsg == CH2)
		{
			Send_Uart_Msg("CH2_VALUE_H");
		}
		else
		{
			Send_Uart_Msg("Higro CH Error");
		}
	}
	else if (firstMsg == Temp)
	{
		if (secondMsg == CH1)
		{
			Send_Uart_Msg("CH1_VALUE_T");
		}
		else if (secondMsg == CH2)
		{
			Send_Uart_Msg("CH2_VALUE_T");
		}
		else
		{
			Send_Uart_Msg("Temp CH Error");
		}
	}
	else if (firstMsg == HigroST)
	{
		if (secondMsg == CH1)
		{
			Send_Uart_Msg("CH1_VALUE_OK");
		}
		else if (secondMsg == CH2)
		{
			Send_Uart_Msg("CH2_VALUE_OK");
		}
		else
		{
			Send_Uart_Msg("HigroST CH Error");
		}
	}

}

void ESP_New_Message(uint8_t *msg, size_t len)
{
	char *token;
	uint8_t cnt = 0;

	First_Message_E firstMsg = Error;
	Second_Message_E secondMsg = Error;
	Third_Message_E thirdMsg = Error;

	int16_t msgBuf[3];

	token = strtok((char*) msg, "_");
	msgBuf[0] = Check_Command(token, commandBuffer1);

	if (msgBuf[0] != Error)
	{
		while (token != NULL)
		{
			cnt += 1;
			token = strtok(NULL, "_");

			if (cnt < 3)
			{
				if (cnt == 1)
				{
					msgBuf[cnt] = Check_Command(token, commandBuffer2);
				}
				else
				{
					msgBuf[cnt] = Check_Command(token, commandBuffer3);
				}

			}
			else
			{
				break;
			}

		}

		firstMsg = msg[0];
		secondMsg = msg[1];
		thirdMsg = msg[2];

		if (secondMsg != -1 && thirdMsg != -1)
		{
			Command_Handling(firstMsg, secondMsg, thirdMsg);
		}

	}

}

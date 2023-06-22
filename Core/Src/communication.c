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

char firstMSG[]="Higro,Temp,HigroStatus";
char secondMSG[]="CH1,CH2";



void ESP_New_Message(uint8_t *msg, size_t len)
{
	char *allocatedMemory;
	char *token;

	uint8_t cnt=1;

	allocatedMemory = malloc(len * sizeof(char));

	memcpy(allocatedMemory, msg, len);

	char firstMsgPart[20];
	char secondMsgPart[20];
	char thirdMsgPart[20];


	token = strtok(allocatedMemory, "_");
	memcpy(firstMsgPart, token, strlen(token));

	while(token!=NULL)
	{
		token = strtok(NULL, "_");

		if(cnt==1)
		{
			memcpy(secondMsgPart, token, strlen(token));
		}
		else if(cnt==2)
		{
			memcpy(thirdMsgPart, token, strlen(token));
		}
		else
		{
			//error
			break;
		}
		cnt++;
	}

	//if()


	free(allocatedMemory);

}

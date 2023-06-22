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





void ESP_New_Message(uint8_t *msg, size_t len)
{
	char *allocatedMemory;
	char *allMsg1;
	char *token;

	uint8_t cnt = 1;
	uint8_t lenIn = 0;

	allocatedMemory = malloc(len * sizeof(char));

	memcpy(allocatedMemory, msg, len);

//	char firstMsgPart[20];
//	char secondMsgPart[20];
//	char thirdMsgPart[20];

	token = strtok(allocatedMemory, "_");
	lenIn = strlen(token);

	/************************************/

	allMsg1= malloc(lenIn*sizeof(char));

	memcpy(allMsg1, token, strlen(token));

	while(token!=NULL)
	{
		token = strtok(NULL, "_");
		lenIn = strlen(token);
		allMsg1= malloc(lenIn*sizeof(char));
		memcpy(allMsg1, token, strlen(token));


	}





	free(allocatedMemory);

}

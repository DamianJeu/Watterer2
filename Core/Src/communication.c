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

static uint8_t msgData[4];
static uint8_t sndMsg[9];
static uint8_t recMsg;

enum
{
	FromEsp = 'E',
	FromStm = 'S',
	Higro = 'H',
	Temperature = 'T',
	HigroStatus = 'A',
	Error = 'e',
	Value = 'V'
};

void ESP_New_Message(uint8_t *msg)
{

	memcpy(msgData, msg, 4);
	recMsg = 1;

}

void Create_Msg_ToSend(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4,
		char *value)
{

	sndMsg[0] = b1;
	sndMsg[1] = b2;
	sndMsg[2] = b3;
	sndMsg[3] = b4;
	sprintf((char*) (sndMsg + 4), "%s", value);
	Send_Uart_Msg(sndMsg, 9);

}

void ESP_Msg_Handling(void)
{

	if (recMsg)
	{

		if (msgData[0] == FromEsp)
		{

			if (msgData[1] == Higro)
			{
				if (msgData[2] == '1')
				{
					Create_Msg_ToSend(FromStm, Higro, '1', Value, "1000");

				}
				else if (msgData[2] == '2')
				{
					Create_Msg_ToSend(FromStm, Higro, '2', Value, "5000");

				}
				else
				{
					//Error
					Create_Msg_ToSend(FromStm, Higro, Error, Error, "eeee");

				}
			}
			else if (msgData[1] == Temperature)
			{
				if (msgData[2] == '1')
				{
					Create_Msg_ToSend(FromStm, Temperature, '1', Value, "0020");

				}
				else if (msgData[2] == '2')
				{
					Create_Msg_ToSend(FromStm, Temperature, '2', Value, "0030");

				}
				else
				{
					//Error
					Create_Msg_ToSend(FromStm, Temperature, Error, Error,
							"eeee");

				}
			}
			else if (msgData[1] == HigroStatus)
			{
				if (msgData[2] == '1')
				{
					Create_Msg_ToSend(FromStm, HigroStatus, '1', Value, "BAD");

				}
				else if (msgData[2] == '2')
				{
					Create_Msg_ToSend(FromStm, HigroStatus, '2', Value, "OK");

				}
				else
				{
					//Error
					Create_Msg_ToSend(FromStm, HigroStatus, Error, Error,
							"eeee");

				}
			}

		}
		else
		{
			Create_Msg_ToSend(FromStm, Error, Error, Error, "eeee");
			Send_Uart_Msg(sndMsg, 9);
		}

		recMsg = 0;
	}

}

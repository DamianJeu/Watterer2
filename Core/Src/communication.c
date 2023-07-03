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
#include "deviceInfo.h"

static uint8_t sndMsg[9];
static uint8_t recMsg;

typedef enum
{
	FromEsp = 'E', FromStm = 'S'

} Device_E;

typedef enum
{
	Higro = 'H', Temperature = 'T', HigroStatus = 'A'

} Function_E;

typedef enum
{
	Error = 'e', Value = 'V'
} Parameter_E;

typedef struct
{

	Device_E Device;
	Function_E Function;
	Parameter_E Channel;
	uint8_t Additional;

} FromEsp_Frame_T;

typedef struct
{
	FromEsp_Frame_T basicData;
	char value[5];

} FromStm_Frame_T;

FromEsp_Frame_T receivedFrame;
FromStm_Frame_T frameToSend;

void ESP_New_Message(uint8_t *msg)
{

	FromEsp_Frame_T *espFramePtr = &receivedFrame;
	memcpy(espFramePtr, msg, 4);
	recMsg = 1;

}

void Create_Msg_ToSend(Device_E b1, Function_E b2, Parameter_E b3, uint8_t b4,
		char *value)
{

	uint8_t *bufPtr = sndMsg;

	*bufPtr = b1;
	*(bufPtr + 1) = b2;
	*(bufPtr + 2) = b3;
	*(bufPtr + 3) = b4;
	sprintf((char*) (sndMsg + 4), "%s", value);
	Send_Uart_Msg(sndMsg, 9);

}

void ESP_Msg_Handling(Critical_Data_T *data)
{

	char textbuf[10];

	if (recMsg)
	{

		if (receivedFrame.Device == FromEsp)
		{

			if (receivedFrame.Function == Higro)
			{
				if (receivedFrame.Channel == '1')
				{
					sprintf(textbuf, "%.3d", data->ch1Higro);
					Create_Msg_ToSend(FromStm, Higro, '1', Value, textbuf);

				}
				else if (receivedFrame.Channel == '2')
				{
					sprintf(textbuf, "%.3d", data->ch2Higro);
					Create_Msg_ToSend(FromStm, Higro, '2', Value, textbuf);

				}
				else
				{
					//Error
					Create_Msg_ToSend(FromStm, Higro, Error, Error, "eeee");

				}
			}
			else if (receivedFrame.Function == Temperature)
			{
				if (receivedFrame.Channel == '1')
				{
					sprintf(textbuf, "%.3d", data->temp);
					Create_Msg_ToSend(FromStm, Temperature, '1', Value,
							textbuf);

				}
				else if (receivedFrame.Channel == '2')
				{
					Create_Msg_ToSend(FromStm, Temperature, '2', Value, "none");

				}
				else
				{
					//Error
					Create_Msg_ToSend(FromStm, Temperature, Error, Error,
							"eeee");

				}
			}
			else if (receivedFrame.Function == HigroStatus)
			{
				if (receivedFrame.Channel == '1')
				{
					if (data->ch1HigroOk)
						memcpy(textbuf, "OK  ", 5);
					else
						memcpy(textbuf, "BAD ",5);

					Create_Msg_ToSend(FromStm, HigroStatus, '1', Value, "BAD");

				}
				else if (receivedFrame.Channel == '2')
				{
					if (data->ch2HigroOk)
						memcpy(textbuf, "OK  ",5);
					else
						memcpy(textbuf, "BAD ",5);
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

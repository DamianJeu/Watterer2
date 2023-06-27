/*
 * deviceInfo.c
 *
 *  Created on: 24 cze 2023
 *      Author: Damia
 */

#include <stdlib.h>

#include "deviceInfo.h"
#include "main.h"
#include "cfg.h"
#include "communication.h"
#include "command.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx_hal_def.h"

void Device_Higro_OK(Critical_Data_T *ptr, GPIO_TypeDef *LD1, GPIO_TypeDef *LD2,
		uint16_t LD1_Pin, uint16_t LD2_Pin)
{

	ptr->ch1HigroOk = ((ptr->ch1Higro) < GetCh1_TooDryVal()) ? 0 : 1;
	ptr->ch2HigroOK = ((ptr->ch2Higro) < GetCh2_TooDryVal()) ? 0 : 1;

	if ((GetCh1_TooDryVal() > ptr->ch1Higro)
			|| (GetCh2_TooDryVal() > ptr->ch2Higro))
	{
		HAL_GPIO_WritePin(LD1, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2, LD2_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LD1, LD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2, LD2_Pin, GPIO_PIN_SET);
	}

}


/*
 * deviceInfo.h
 *
 *  Created on: 24 cze 2023
 *      Author: Damia
 */

#ifndef INC_DEVICEINFO_H_
#define INC_DEVICEINFO_H_

#include "main.h"

typedef struct
{
	uint16_t ch1Raw;
	uint16_t ch2Raw;
	uint16_t ch1Higro;
	uint16_t ch2Higro;
	uint8_t ch1HigroOk;
	uint8_t ch2HigroOk;
	int16_t temp;

}Critical_Data_T;

void Device_Higro_OK(Critical_Data_T *ptr, GPIO_TypeDef *LD1, GPIO_TypeDef *LD2, uint16_t LD1_Pin, uint16_t LD2_Pin);


#endif /* INC_DEVICEINFO_H_ */

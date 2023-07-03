/*
 * communication.h
 *
 *  Created on: 22 cze 2023
 *      Author: djeutner
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#include "deviceInfo.h"


void ESP_Msg_Handling(Critical_Data_T *data);
void ESP_New_Message(uint8_t *msg);

#endif /* INC_COMMUNICATION_H_ */

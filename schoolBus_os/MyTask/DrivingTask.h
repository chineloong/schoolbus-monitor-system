#ifndef __DRIVINGTASK_H__
#define __DRIVINGTASK_H__

#include "stm32f4xx.h"



extern volatile int drivingType;
extern uint8_t DrivingReceive;

void DrivingTask_Init(void);
void DrivingType_Handler(void);
void DrivingTask(void* pvParameters);
#endif

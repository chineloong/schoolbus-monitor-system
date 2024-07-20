#ifndef __DRIVINGTASK_H__
#define __DRIVINGTASK_H__

#include "stm32f4xx.h"


#define Normal '0'
#define Sleep '1'
#define Phone '2'
#define NoPerson '3'


extern volatile int drivingType;
extern uint8_t DrivingReceive;

extern uint8_t sleepydrivingFlag;
extern uint8_t phonedrivingFlag;

void DrivingTask_Init(void);
void DrivingType_Handler(void);
void DrivingTask(void* pvParameters);
#endif

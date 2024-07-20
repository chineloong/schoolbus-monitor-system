#ifndef __BROCAST_TASK_H
#define __BROCAST_TASK_H

#include "stm32f4xx.h"


enum BroadcastType
{
		Normal,
		Refresh,
		Skip,
		SleepyDriving,
		PhoneDriving,
		CheckCard
};

extern enum BroadcastType sendType;
extern volatile char broadcastmsg[200];
extern volatile int isBroadcast_Enable;


void Broadcast(enum BroadcastType Type);
void Brocast_Task(void* pvParameters);
#endif

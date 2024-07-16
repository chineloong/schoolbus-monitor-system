#ifndef __4G_H
#define __4G_H

#include "stm32f4xx.h"

// ���崮��1�ķ��ͺͽ��ջ�������С
#define TX_BUFFER_SIZE 128
#define RX_BUFFER_SIZE 128

extern char txBuffer[TX_BUFFER_SIZE];
extern char rxBuffer[RX_BUFFER_SIZE];
extern uint8_t rxData;
extern char receiveData[RX_BUFFER_SIZE];

void Net_send(const char* data);
void Net_Config(void);

#endif

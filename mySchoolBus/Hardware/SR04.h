#ifndef __SR04_H
#define __SR04_H
#include "main.h"
#include "tim.h"
#include "stdio.h"
 
#define TRIG_H  HAL_GPIO_WritePin(first_supersonic_GPIO_Port,first_supersonic_Pin,GPIO_PIN_SET)
#define TRIG_L  HAL_GPIO_WritePin(first_supersonic_GPIO_Port,first_supersonic_Pin,GPIO_PIN_RESET)
#define TRIG2_H  HAL_GPIO_WritePin(second_supersonic_GPIO_Port,second_supersonic_Pin,GPIO_PIN_SET)
#define TRIG2_L  HAL_GPIO_WritePin(second_supersonic_GPIO_Port,second_supersonic_Pin,GPIO_PIN_RESET)
 
struct SR04
{
		float distance1;//����
		float distance2;
		int8_t measure_state1;//״̬��־λ
		int8_t measure_state2;

};


void SR04_Init(void);
void SR04_GetData(void);
 
#endif

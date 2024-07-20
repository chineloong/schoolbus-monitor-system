#ifndef __SR04_H
#define __SR04_H
#include "main.h"
#include "tim.h"
#include "stdio.h"

#define TRIG_H HAL_GPIO_WritePin(superrsonic_tirgger_GPIO_Port, superrsonic_tirgger_Pin, GPIO_PIN_SET)
#define TRIG_L HAL_GPIO_WritePin(superrsonic_tirgger_GPIO_Port, superrsonic_tirgger_Pin, GPIO_PIN_RESET)
#define TRIG2_H HAL_GPIO_WritePin(superrsonic2_tirgger_GPIO_Port, superrsonic2_tirgger_Pin, GPIO_PIN_SET)
#define TRIG2_L HAL_GPIO_WritePin(superrsonic2_tirgger_GPIO_Port, superrsonic2_tirgger_Pin, GPIO_PIN_RESET)

struct SR04
{

	float raw_distance1; // 原始距离
	float raw_distance2;
	float distance1; // 距离
	float distance2;
	float time1;
	float time2;
	int8_t measure_state1; // 状态标志位
	int8_t measure_state2;
	int8_t refreshflag1;
	int8_t refreshflag2;
};

extern int flag;
extern int BusFlag;

void SR04_Init(void);
void SR04_GetData(void);
void intoBus(void);
void cardWarning(void);

#endif

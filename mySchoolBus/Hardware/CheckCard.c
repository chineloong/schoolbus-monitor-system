#include "stm32f4xx.h"
#include "CheckCard.h"
#include "SR04.h"

extern struct SR04 SR04;

enum BusState intoBusFlag,outofBusFlag;

//检测上车
void intoBus(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 1.0f && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 1.0f && SR04.distance2 >= 0.2f)
		{
				SR04.time2 = HAL_GetTick();
				refreshflag2 = 1;
		}
		
		if(refreshflag1 && refreshflag2)
		{
				if(SR04.time2 > SR04.time1)
						intoBusFlag = intoBus_1;
				else 
						intoBusFlag = intoBus_0;
				
				refreshflag1 = refreshflag2 = 0;
		}
		
}
//检测下车
void outofBus(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 1.0f && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 1.0f && SR04.distance2 >= 0.2f)
		{
				SR04.time2 = HAL_GetTick();
				refreshflag2 = 1;
		}
		
		if(refreshflag1 && refreshflag2)
		{
				if(SR04.time2 < SR04.time1)
						outofBusFlag = outofBus_1;
				else 
						outofBusFlag = outofBus_0;
				
				refreshflag1 = refreshflag2 = 0;
		}

}	

//上车刷卡机制
int flag = 0;
void cardWarning(void)
{
		static int8_t lastSum = 0;
		
		//上车并刷卡
		if(flag == 0 && lastSum < mynfc.sumCard)
		{
				flag = 1;
				lastSum = mynfc.sumCard;
		
		}
		//刷卡后通过
		if(flag == 1 && intoBusFlag == intoBus_1)
				flag = 2;
		//复位
		else if(flag == 2)
		{
				flag = 0;
				intoBusFlag = intoBus_0;
				SR04.time1 = SR04.time2 = 0;
		}
			
		//上车但是没有刷卡
		if(flag == 0 && intoBusFlag == intoBus_1)
				flag = 3;
		
		//没有刷卡开启警报
		if(flag == 3)
		{
				WarningStart;
				flag = 4;
		}
		//刷卡后关闭警报
		else if(flag == 4 && lastSum < mynfc.sumCard)
		{
				lastSum = mynfc.sumCard;
				WarningStop;
				flag = 0;
				intoBusFlag = intoBus_0;
			
				SR04.time1 = SR04.time2 = 0;
		}

}


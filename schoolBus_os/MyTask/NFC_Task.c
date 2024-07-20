#include "NFC_Task.h"
#include "NFC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "SR04.h"


extern struct SR04 SR04;

volatile enum BusState intoBusFlag,outofBusFlag;
enum StudentState studentState;

#define LOWPASS 0.8f


float sum1[20];
float sum2[20];
	
/**
 * @description: 根据一段时间的超声波数据求平均值平滑
 * @return {*}
 */
void AverageFilter(float distance1,float distance2)
{
	

	static int8_t i = 0;

	if(i < 20)
	{
		sum1[i] = distance1;
		sum2[i] = distance2;
		i++;
	}
	else
	{
		i = 0;
	}
	//SR04.distance1 = sum();
	SR04.distance2 = (sum2[0] + sum2[1] + sum2[2] + sum2[3] + sum2[4]) / 5;

}

//检测上车
void intoBusCheck(void)
{
//		static int8_t refreshflag1 = 0;
//		static int8_t refreshflag2 = 0;
//	
		static int8_t sum1 = 0;
		static int8_t sum2 = 0;
		
		static float lastDistance1 = 0;
		static float lastDistance2 = 0;

		float distance1;
		float distance2;

		//一阶低通滤波
		distance1 =LOWPASS * SR04.raw_distance1 + (1-LOWPASS) * lastDistance1;
		distance2 =LOWPASS * SR04.raw_distance2 + (1-LOWPASS) * lastDistance2;

		lastDistance1 = distance1;
		lastDistance2 = distance2;

		AverageFilter(distance1,distance2);

		if(SR04.distance1 <= 0.5  && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				SR04.refreshflag1 = 1;
		}
		
		
		if(SR04.distance2 <= 0.5f && SR04.distance2 >= 0.2f)
		{
				SR04.time2 = HAL_GetTick();
				SR04.refreshflag2 = 1;
		}
		

		if(SR04.refreshflag1 && SR04.refreshflag2)
		{
				if(SR04.time2 > SR04.time1)
						intoBusFlag = intoBus_1;
				else 
						intoBusFlag = intoBus_0;
				
				SR04.refreshflag1 = SR04.refreshflag2 = 0;
		}
		
}
//检测下车
//void outofBusCheck(void)
//{
//		static int8_t refreshflag1 = 0;
//		static int8_t refreshflag2 = 0;
//		if(SR04.distance1 <= 1.0f && SR04.distance1 >= 0.2f)
//		{
//				SR04.time1 = HAL_GetTick();
//				refreshflag1 = 1;
//		}
//		if(SR04.distance2 <= 1.0f && SR04.distance2 >= 0.2f)
//		{
//				SR04.time2 = HAL_GetTick();
//				refreshflag2 = 1;
//		}
//		
//		if(refreshflag1 && refreshflag2)
//		{
//				if(SR04.time2 < SR04.time1)
//						outofBusFlag = outofBus_1;
//				else 
//						outofBusFlag = outofBus_0;
//				
//				refreshflag1 = refreshflag2 = 0;
//		}

//}	

//上车刷卡机制
int flag = 0;
uint32_t waitCircle = 0;
void cardWarning(void)
{
        //上次的刷卡总数
		static int8_t lastSum = 0;
        //未刷卡的等待时间
		

		//上车并刷卡
		if(studentState == waiting && lastSum < mynfc.sumCard)
		{
					studentState = onBus_checked;
					lastSum = mynfc.sumCard;
//				studentID_Send();		
		}
		//刷卡后通过
		if(studentState == onBus_checked && intoBusFlag == intoBus_1)
        {
            studentState = waiting;
            intoBusFlag = intoBus_0;
            SR04.time1 = SR04.time2 = 0;
        }

		//上车但是没有刷卡
		if(studentState == waiting && intoBusFlag == intoBus_1)
				studentState = onBus_unchecked;
		
		//没有刷卡开启警报
		if(studentState == onBus_unchecked)
		{
            //启用刷卡警报，一次;

            //如果一定时间内mynfc.sumCard没有变化，说明没有刷卡，跳过
            while(lastSum >= mynfc.sumCard)
            {                
                waitCircle++;
                if(waitCircle > 2500000)
                {
                    waitCircle = 0;
                    break;
                }
						}

            //如果一定时间内mynfc.sumCard有变化，说明有刷卡，跳过
            if(lastSum < mynfc.sumCard)
            {
                
                lastSum = mynfc.sumCard;
                
            }
						studentState = waiting;
						intoBusFlag = intoBus_0;
						waitCircle = 0;

						SR04.time1 = SR04.time2 = 0;

        }


}

/**
 * @description: NFC寻卡读卡任务
 * @return {*}
 */
void NFC_Task(void* pvParameters)
{
    while(1)
    { 
			SR04_GetData();
			intoBusCheck();
			//outofBusCheck();
			nfc_findCard();
			cardWarning();
			vTaskDelay(50);
    }
}

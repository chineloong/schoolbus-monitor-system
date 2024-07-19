#include "NFC_Task.h"
#include "NFC.h"
#include "freeRTOS.h"
#include "SR04.h"


extern struct SR04 SR04;

enum BusState intoBusFlag,outofBusFlag;
enum StudentState studentState;

//检测上车
void intoBusCheck(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 0.6f && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 0.6f && SR04.distance2 >= 0.2f)
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
void outofBusCheck(void)
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
        //上次的刷卡总数
		static int8_t lastSum = 0;
        //未刷卡的等待时间
		static int8_t waitCircle = 0;

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
                if(waitCircle > 50)
                {
                    waitCircle = 0;
                    break;
                }
		    }

            //如果一定时间内mynfc.sumCard有变化，说明有刷卡，跳过
            if(lastSum < mynfc.sumCard)
            {
                studentState = waiting;
                lastSum = mynfc.sumCard;
                intoBusFlag = intoBus_0;
                waitCircle = 0;

                SR04.time1 = SR04.time2 = 0;
            }

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
        nfc_findCard();
        vTaskDelay(100);
    }
}

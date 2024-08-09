#include "NFC_Task.h"
#include "NFC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Brocast_Task.h"


volatile enum BusState intoBusFlag,outofBusFlag,Busstate;
enum StudentState studentState;

float check1_time;
float check2_time;


float lasttime = 0;
int8_t lastSum = 0;


void Bus_check(void)
{



}
//上车刷卡机制
int flag = 0;
uint32_t waitCircle = 0;
//void cardWarning(void)
//{
//        //上次的刷卡总数
//		static int8_t lastSum = 0;
//        //未刷卡的等待时间
//		

//		//上车并刷卡
//		if(studentState == waiting && lastSum < mynfc.sumCard)
//		{
//					studentState = onBus_checked;
//					lastSum = mynfc.sumCard;
////				studentID_Send();		
//		}
//		//刷卡后通过
//		if(studentState == onBus_checked && intoBusFlag == intoBus_1)
//        {
//            studentState = waiting;
//            intoBusFlag = intoBus_0;
//            SR04.time1 = SR04.time2 = 0;
//        }

//		//上车但是没有刷卡
//		if(studentState == waiting && intoBusFlag == intoBus_1)
//				studentState = onBus_unchecked;
//		
//		//没有刷卡开启警报
//		if(studentState == onBus_unchecked)
//		{
//            //启用刷卡警报，一次;

//            //如果一定时间内mynfc.sumCard没有变化，说明没有刷卡，跳过
//            while(lastSum >= mynfc.sumCard)
//            {                
//                waitCircle++;
//                if(waitCircle > 2500000)
//                {
//                    waitCircle = 0;
//                    break;
//                }
//						}

//            //如果一定时间内mynfc.sumCard有变化，说明有刷卡，跳过
//            if(lastSum < mynfc.sumCard)
//            {
//                
//                lastSum = mynfc.sumCard;
//                
//            }
//						studentState = waiting;
//						intoBusFlag = intoBus_0;
//						waitCircle = 0;

//						SR04.time1 = SR04.time2 = 0;

//        }


//}


void cardWarning(void)
{
	
	
		
	if(lastSum < mynfc.sumCard)
		{
				
				lastSum = mynfc.sumCard;
							
				lasttime = HAL_GetTick();
				intoBusFlag = midstate;
				
		}
		else if(intoBusFlag == midstate)
		{
//				if((HAL_GetTick() - lasttime) > 5000)
//				{
//							
							osDelay(5000);
							intoBusFlag = intoBus_0;
//				}
//			
		
		}
		else if(lastSum >= mynfc.sumCard && intoBusFlag == state_change &&(HAL_GetTick() - lasttime) > 1500)
		{
				while (isBroadcast_Enable != 1)
				{
					__NOP();
				};
				
				isBroadcast_Enable = 0;
				
				intoBusFlag = intoBus_0;
				Broadcast(CheckCard,NULL);
				lastSum = mynfc.sumCard;
				
				lasttime = HAL_GetTick();
				osDelay(500);
				
				
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
//			if(intoBusFlag == intoBus_0)
//					intoBusCheck();
			//outofBusCheck();
			nfc_findCard();
			cardWarning();
			vTaskDelay(50);
    }
}

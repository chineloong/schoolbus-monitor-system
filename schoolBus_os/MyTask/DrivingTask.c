#include "DrivingTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "4G.h"
#include "stdio.h"
#include "Brocast_Task.h"

extern UART_HandleTypeDef huart2;



volatile int drivingType;
uint8_t DrivingReceive;
int8_t Broadtype;


uint8_t MidState = 0;
uint8_t sleepydrivingFlag = 0;
uint8_t phonedrivingFlag = 0;

void DrivingTask_Init(void)
{
    HAL_UART_Receive_IT(&huart2,(uint8_t *)&DrivingReceive,1);
     
}
int sleepsum = 0;
int phonesum = 0;
int normalsum = 0;
void DrivingType_Handler(void)
{
    //状态计数，三次的时候认为危险驾驶
    if(MidState != 1)
		{
				if(drivingType == Sleep)
				{
						sleepsum++;
						phonesum=0;
						normalsum=0;
				}
				else if(drivingType == Phone)
				{
						sleepsum=0;
						phonesum++;
						normalsum=0;
				}
				else if(drivingType == NormalDriving || drivingType == NoPerson)
				{
						sleepsum = 0;
						phonesum=0;
						normalsum++;
						Broadtype = NormalDriving;
				}
		}
		else
		{
				if(drivingType == NormalDriving || drivingType == NoPerson)
				{
						sleepsum = 0;
						phonesum=0;
						normalsum++;
						Broadtype = NormalDriving;
				}
		
		
		}
			
    if(sleepsum>=5)
		{		
				Broadtype = Sleep;
        sleepydrivingFlag = 1;
				MidState = 1;

		}

		else if(phonesum>=5)
		{
				
				Broadtype = Phone;
        phonedrivingFlag = 1;
				MidState = 1;
		}
		else if(normalsum>=10)
		{
				normalsum = 0;
				Broadtype = NormalDriving;
				MidState = 0;

		}
}

/**
 * @description: 驾驶违规警告任务
 * @return {*}
 */
void DrivingTask(void* pvParameters)
{
    while(1)
    {
        if(Broadtype == Sleep)
        {
            while(isBroadcast_Enable != 1)
            {
							__NOP();
            };
            Broadcast(SleepyDriving,NULL);
            isBroadcast_Enable = 0;
						sleepsum = 0;
						Broadtype = NormalDriving;
        }
        if(Broadtype == Phone)
        {
            while(isBroadcast_Enable != 1)
            {
							__NOP();
            };
            Broadcast(PhoneDriving,NULL);
            isBroadcast_Enable = 0;
						phonesum = 0;
						Broadtype = NormalDriving;
        }

				
        vTaskDelay(200);
    }

}

#include "DrivingTask.h"
#include "freeRTOS.h"
#include "4G.h"
#include "stdio.h"
#include "Brocast_Task.h"

extern UART_HandleTypeDef huart2;

#define Normal '0'
#define Sleep '1'
#define Phone '2'
#define NoPerson '3'

volatile int drivingType;
uint8_t DrivingReceive;
int8_t Broadtype;
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
    else if(drivingType == Normal || drivingType == NoPerson)
    {
        sleepsum = 0;
				phonesum=0;
				normalsum++;
			  Broadtype = Normal;
    }

    if(sleepsum>=5)
		{
				char sleepChar[3];
				sprintf(sleepChar, "#%d", Sleep);
				Net_sendChar(sleepChar);
				
				Broadtype = Sleep;

		}

		else if(phonesum>=5)
		{
				char phoneChar[3];
				sprintf(phoneChar, "#%d", Phone);
				Net_sendChar(phoneChar);
				
				Broadtype = Phone;
		}
		else if(normalsum>=2)
		{
				normalsum = 0;
				Broadtype = Normal;

		}
}
int mytest = 0;
/**
 * @description: 驾驶违规警告任务
 * @return {*}
 */
void DrivingTask(void* pvParameters)
{
    while(1)
    {
				mytest++;
        if(Broadtype == Sleep)
        {
            while(isBroadcast_Enable != 1)
            {
							__NOP();
            };
            Broadcast(SleepyDriving);
            isBroadcast_Enable = 0;
						Broadtype = Normal;
						sleepsum = 0;
        }
        if(Broadtype == Phone)
        {
            while(isBroadcast_Enable != 1)
            {
							__NOP();
            };
            Broadcast(PhoneDriving);
            isBroadcast_Enable = 0;
						Broadtype = Normal;
						phonesum = 0;
        }

				
        vTaskDelay(200);
    }

}

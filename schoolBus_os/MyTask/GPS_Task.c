#include "stdio.h"
#include "string.h"
#include "GPS_Task.h"
#include "GPS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "4G.h"
#include "SR04.h"
#include "nfc.h"
#include "voiceMiddleware.h"
#include "DrivingTask.h"

extern UART_HandleTypeDef huart1;
float test = 110.1f;


/**
 * @description: GPS数据发送
 * @return {*}
 */
void GPS_Send(void)
{
    char msg[100];
    int size;
		static char lastPos[100] = "!0,0,0";
//    
   if(GPS.isUsefull)//
   {
       //sprintf(msg,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       size = snprintf(msg,100,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       Net_send(msg,size);
       test++;
				strcpy(lastPos,msg);
   }
	 else
	 {
				Net_send(lastPos,strlen(lastPos));
	 }
//		sprintf(msg,"!%f,%f,%f",33.56455,114.25325466,130.066);
//		Net_send(msg,strlen(msg));
//		test++;

}



/**
 * @description: FreeRTOS  GPS任务函数
 * @return {*}
 */
int testMsg = 0;
char mytest[]="13975910962,你好，你的孩子";
void NetSend_Task(void* pvParameters)
{
	
	HAL_UART_Receive_IT(&huart1,&GPS_data,1);
	SR04_Init();

    while(1)
    {
		parseGpsBuffer();
		GPS_Send();
		
		vTaskDelay(1000);

		if(Net_TrasformFlag == 1)
		{
			char msg[100];
			sprintf(msg,"A%u",mynfc.CardID);
			taskENTER_CRITICAL();
			Net_send(msg,strlen(msg));
			taskEXIT_CRITICAL();
			Net_TrasformFlag =  0;

			vTaskDelay(100);	
		}

		if(sleepydrivingFlag == 1)
		{
			
			char sleepChar[3];
			sprintf(sleepChar, "#%c", Sleep);
			
			Net_sendChar(sleepChar);
			sleepydrivingFlag = 0;
			vTaskDelay(100);
		}
		if(phonedrivingFlag == 1)
		{	
			
			char phoneChar[3];
			sprintf(phoneChar, "#%c", Phone);
			Net_sendChar(phoneChar);
			
			
			Net_sendChar(phoneChar);
			phonedrivingFlag = 0;
			vTaskDelay(100);
		}


    }
}

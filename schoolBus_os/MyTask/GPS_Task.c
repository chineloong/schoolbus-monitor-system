#include "stdio.h"
#include "GPS_Task.h"
#include "GPS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "4G.h"
#include "SR04.h"

#include "voiceMiddleware.h"
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
    
   if(GPS.isUsefull)//
   {
       //sprintf(msg,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       size = snprintf(msg,100,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       Net_send(msg,size);
       test++;
   }
//		sprintf(msg,"!%f,%f,%f",100.00f,200.1f,100.0f);
//		Net_send(msg);
		test++;

}



/**
 * @description: FreeRTOS  GPS任务函数
 * @return {*}
 */
void GPS_Task(void* pvParameters)
{
	
		HAL_UART_Receive_IT(&huart1,&GPS_data,1);
		SR04_Init();
    while(1)
    {
        parseGpsBuffer();
        GPS_Send();
				
        vTaskDelay(200);
    }
}

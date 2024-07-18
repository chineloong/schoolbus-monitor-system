#include "stdio.h"
#include "GPS_Task.h"
#include "GPS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "4G.h"
#include "SR04.h"


extern UART_HandleTypeDef huart1;
float test = 110.1f;


/**
 * @description: 发送GPS数据
 * @return {*}
 */
void GPS_Send(void)
{
    char msg[100];
    //int size;
    
   if(GPS.isUsefull)//
   {
       sprintf(msg,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       //size = snprintf(msg,100,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
       Net_send(msg);
       test++;
   }
//		sprintf(msg,"!%f,%f,%f",100.00f,200.1f,100.0f);
//		Net_send(msg);
		test++;

}



/**
 * @description: FreeRTOS任务函数，发送GPS数据
 * @return {*}
 */
void GPS_Task(void* pvParameters)
{
	
		HAL_UART_Receive_IT(&huart1,&GPS_data,1);
		SR04_Init();
    while(1)
    {
        // Add your code here
        parseGpsBuffer();
				SR04_GetData();
        GPS_Send();
        vTaskDelay(200);
    }
}

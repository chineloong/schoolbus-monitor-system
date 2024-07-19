#include "DrivingTask.h"
#include "freeRTOS.h"
#include "4G.h"
#include "stdio.h"

extern UART_HandleTypeDef huart2;

#define Normal '0'
#define Sleep '1'
#define Phone '2'
#define NoPerson '3'

int drivingType;
uint8_t DrivingReceive;

void DrivingTask_Init(void)
{
    HAL_UART_Receive_IT(&huart2,(uint8_t *)&DrivingReceive,1);
     
}

void DrivingType_Handler(void)
{
    //状态计数，三次的时候认为危险驾驶
    static int sum = 0;
    int flag;
    if(drivingType == Sleep)
    {
        sum++;
        flag = 1;
    }
    else if(drivingType == Phone)
    {
        sum++;
        flag = 2;
    }
    else if(drivingType == Normal)
    {
        sum = 0;
        flag = 0;
    }

    if(sum>=3)
    {
        if(flag == 1)
        {
            char sleepChar[3];
            sprintf(sleepChar, "%d", Sleep);
            Net_sendChar(sleepChar);
            sum = 0;
        }

        else if(flag == 2)
        {
            char phoneChar[3];
            sprintf(phoneChar, "%d", Phone);
            Net_sendChar(phoneChar);
            sum = 0;
        }
    }
}


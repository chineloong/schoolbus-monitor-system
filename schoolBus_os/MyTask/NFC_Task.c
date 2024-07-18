#include "NFC_Task.h"
#include "NFC.h"
#include "FreeRTOS.h"

/**
 * @description: NFC寻卡读卡任务
 * @return {*}
 */
void NFC_Task(void* pvParameters)
{
    while(1)
    { 
        nfc_findCard();
        vTaskDelay(100);
    }
}
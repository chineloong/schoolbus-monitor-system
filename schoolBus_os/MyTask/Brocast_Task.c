#include "Brocast_Task.h"
#include "FreeRTOS.h"
#include "voiceMiddleware.h"
#include "stdio.h"
#include "string.h"

enum BroadcastType sendType;
volatile char broadcastmsg[200];
volatile int isBroadcast_Enable = 1;

//疲劳驾驶通知
char sleepydriving[]={0xC4,0xFA,0xD2,0xD1,0xC6,0xA3,0xC0,0xCD,0xBC,0xDD,0xCA,0xBB,0xA3,0xAC,0xC7,0xEB,0xD7,0xA2,0xD2,0xE2,0xD0,0xDD,0xCF,0xA2,0x00};
//开车打电话通知
char phonedriving[]={0xC7,0xEB,0xCE,0xF0,0xBF,0xAA,0xB3,0xB5,0xB4,0xF2,0xB5,0xE7,0xBB,0xB0,0xA3,0xAC,0xD7,0xA2,0xD2,0xE2,0xBD,0xBB,0xCD,0xA8,0xB0,0xB2,0xC8,0xAB,0x00};
//刷卡通知
char checkcard[]={0xC9,0xCF,0xB3,0xB5,0xC7,0xEB,0xCB,0xA2,0xBF,0xA8,0x00};


/**
* @brief         自定义发送语音
* @param[in]      none
* @retval         none
*/
void Broadcast(enum BroadcastType Type)
{
		switch(Type)
		{
			case Normal:
				
				sprintf((char *)text_recv.text_buffer,"%s",broadcastmsg);
				
				/* 必须紧跟sprintf(复制粘贴即可) */
				//求sentence length
				// text_recv.buffer_size = sizeof(text_recv.text_buffer)/sizeof(text_recv.text_buffer[0])-1;
				text_recv.buffer_size = strlen((const char *)broadcastmsg);
				
				if( text_recv.text_buffer[text_recv.buffer_size-1] == 0 ){
					text_recv.sentense_length = strlen((const char *)text_recv.text_buffer);
				}
				else
					text_recv.sentense_length = text_recv.buffer_size;	
				//执行单次发送
				Voice_Sendmsg(text_recv.text_buffer,text_recv.sentense_length);	
				/* ---------复制粘贴结束---------*/
				
				break;
			case Refresh:
				/* 必须和sprintf 不同时执行*/
				voice_packer.clearvoice();
				break;
			
			case Skip:
				break;
			
			case SleepyDriving:
				sprintf((char *)text_recv.text_buffer,"%s",sleepydriving);
				
				/* 必须紧跟sprintf(复制粘贴即可) */
				//求sentence length
				// text_recv.buffer_size = sizeof(text_recv.text_buffer)/sizeof(text_recv.text_buffer[0])-1;
				text_recv.buffer_size = strlen(sleepydriving);
				
				if( text_recv.text_buffer[text_recv.buffer_size-1] == 0 ){
					text_recv.sentense_length = strlen((const char *)text_recv.text_buffer);
				}
				else
					text_recv.sentense_length = text_recv.buffer_size;	
				//执行单次发送
				Voice_Sendmsg(text_recv.text_buffer,text_recv.sentense_length);	
				/* ---------复制粘贴结束---------*/
				break;

			case PhoneDriving:
				sprintf((char *)text_recv.text_buffer,"%s",phonedriving);
				
				/* 必须紧跟sprintf(复制粘贴即可) */
				//求sentence length
				// text_recv.buffer_size = sizeof(text_recv.text_buffer)/sizeof(text_recv.text_buffer[0])-1;
				text_recv.buffer_size = strlen(phonedriving);
				
				if( text_recv.text_buffer[text_recv.buffer_size-1] == 0 ){
					text_recv.sentense_length = strlen((const char *)text_recv.text_buffer);
				}
				else
					text_recv.sentense_length = text_recv.buffer_size;	
				//执行单次发送
				Voice_Sendmsg(text_recv.text_buffer,text_recv.sentense_length);	
				/* ---------复制粘贴结束---------*/
				break;

			default:
				break;
			
		}
}


/**
 * @description: 广播任务,实现扩音器资源调用
 * @return {*}
 */
void Brocast_Task(void* pvParameters)
{
    while(1)
    {
        if(isBroadcast_Enable == 0)
        {
            osDelay(6000);
            Broadcast(Refresh);
            isBroadcast_Enable = 1;
        }
        
        vTaskDelay(20);
    }
}

#include "NetBroadcast.h"
#include "4G.h"
#include "Brocast_Task.h"
#include "string.h"
#include "stdio.h"
#include "cmsis_os.h"

extern int broadcastmsgFlag;
extern int msgSendFlag;

char broadcastmsg[RX_BUFFER_SIZE];
char msgSendFrame[RX_BUFFER_SIZE];
/**
 * @description: 4G数据广播函数
 * @return {*}
 */
void NetBroadcastTask(void)
{

	while (1)
	{
		
		if (broadcastmsgFlag == 1)
		{
			//sprintf(broadcastmsg, "%s", &receiveData[1]);
			while (isBroadcast_Enable != 1)
			{
				__NOP();
			};

			isBroadcast_Enable = 0;
			Broadcast(NormalDriving, broadcastmsg);

			memset(broadcastmsg, 0, RX_BUFFER_SIZE);
			broadcastmsgFlag = 0;
			//memset(receiveData, 0, RX_BUFFER_SIZE);
		}
		
		else if(msgSendFlag == 1)
		{
		
			while (isBroadcast_Enable != 1)
			{
				__NOP();
			};
			
			char broadcastTempMsg[RX_BUFFER_SIZE];
			uint8_t length = (uint8_t)msgSendFrame[0];
			memcpy(broadcastTempMsg,&msgSendFrame[1],length);
			isBroadcast_Enable = 0;
			broadcastTempMsg[length]=0;
			Broadcast(NormalDriving, broadcastTempMsg);
			
			sprintf(broadcastTempMsg,&msgSendFrame[length+1]);
			Net_SendShortMsg(broadcastTempMsg);
			
			msgSendFlag = 0;
		}
		vTaskDelay(100);
	}
}

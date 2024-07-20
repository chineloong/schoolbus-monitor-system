#include "NetBroadcast.h"
#include "4G.h"
#include "Brocast_Task.h"
#include "string.h"
#include "stdio.h"
#include "cmsis_os.h"

extern int broadcastmsgFlag;
char broadcastmsg[RX_BUFFER_SIZE];
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
		vTaskDelay(100);
	}
}

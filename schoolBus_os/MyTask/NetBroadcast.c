#include "NetBroadcast.h"
#include "4G.h"
#include "Brocast_Task.h"
#include "string.h"
#include "stdio.h"


void NetBroadcastTask(void)
{
	
		while(1)
		{
				if(receiveData[0]=='!')
				{
						sprintf(broadcastmsg,"%s",&receiveData[1]);
						while(isBroadcast_Enable != 1)
            {
							__NOP();
            };
            Broadcast(Normal);
            isBroadcast_Enable = 0;
						memset(broadcastmsg,0,200);
						memset(receiveData,0,200);
				
				}
				vTaskDelay(100);
		
		}
}
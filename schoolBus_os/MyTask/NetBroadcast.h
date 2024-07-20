#ifndef __NETBROADCAST_H
#define __NETBROADCAST_H

#include "stm32f4xx.h"
#include "4G.h"

extern char broadcastmsg[RX_BUFFER_SIZE];
void NetBroadcastTask(void);

#endif

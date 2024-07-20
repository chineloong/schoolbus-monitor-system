#ifndef __LOWPASSFILTER_H
#define __LOWPASSFILETE_H

#include "stm32f4xx.h"

// 定义滤波器结构体  
typedef struct {  
    int bufferSize;  // 缓冲区大小  
    int *buffer;     // 存储数据的缓冲区  
    int head;        // 缓冲区头指针  
    int sum;         // 当前缓冲区内所有数据的和  
    int count;       // 当前缓冲区中的数据点数量  
} LowPassFilter;  

#endif

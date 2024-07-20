
#include "LowPassFilter.h"
#include "FreeRTOS.h"
#include "stdlib.h"


// 初始化滤波器  
void initLowPassFilter(LowPassFilter *filter, int bufferSize) {  
    filter->bufferSize = bufferSize;  
    filter->buffer = (int *)malloc(bufferSize * sizeof(int));  
    if (!filter->buffer) {  
        //fprintf(stderr, "Memory allocation failed\n");  
        exit(EXIT_FAILURE);  
    }  
    filter->head = 0;  
    filter->sum = 0;  
    filter->count = 0;  
}  
  
// 添加新数据到滤波器  
void addDataToFilter(LowPassFilter *filter, int newData) {  
    // 移除旧数据  
    if (filter->count >= filter->bufferSize) {  
        filter->sum -= filter->buffer[filter->head];  
        filter->head = (filter->head + 1) % filter->bufferSize;  
    }  
  
    // 添加新数据  
    filter->buffer[filter->head] = newData;  
    filter->sum += newData;  
    if (filter->count < filter->bufferSize) {  
        filter->count++;  
    }  
}  
  
// 获取滤波后的数据（平均值）  
double getFilteredData(LowPassFilter *filter) {  
    if (filter->count == 0) {  
        return 0.0; // 如果还没有数据，则返回0  
    }  
    return (double)filter->sum / filter->count;  
}  
  
// 清理资源  
void cleanupLowPassFilter(LowPassFilter *filter) {  
    free(filter->buffer);  
}  
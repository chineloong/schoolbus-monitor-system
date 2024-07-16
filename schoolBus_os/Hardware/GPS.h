#ifndef	__GPS_H
#define __GPS_H

#include "stm32f4xx.h"                  // Device header

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

extern uint8_t GPS_Frame[USART_REC_LEN];
extern uint8_t GPS_data;

#define false 0
#define true 1

//定义数组长度
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 
#define knot_length 5

typedef struct GPSData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//是否获取到GPS数据
	char isParseData;	//是否解析完成
	char UTCTime[UTCTime_Length];		//UTC时间
	char raw_latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char raw_longitude[longitude_Length];		//经度
	char E_W[E_W_Length];		//E/W
	char knot[knot_length];//节速度
	char isUsefull;		//定位信息是否有效
	float latitude;
	float longitude;
	float speed;
} GPSData;

#define x_pi  3.14159265358979324f * 3000.0f / 180.0f
#define pi  3.1415926535897932384626f  // π
#define a  6378245.0f  //长半轴
#define ee  0.00669342162296594323f  //扁率


extern uint8_t GPS_Frame[USART_REC_LEN];
extern uint8_t GPS_data;

extern GPSData GPS;

void parseGpsBuffer(void);
void wgs84togcj02(float *lng, float *lat);

#endif


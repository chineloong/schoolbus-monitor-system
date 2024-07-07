#ifndef	__GPS_H
#define __GPS_H

#include "stm32f4xx.h"                  // Device header


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
extern uint8_t GPS_Frame[USART_REC_LEN];
extern uint8_t GPS_data;


#define false 0
#define true 1

//�������鳤��
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
	char isGetData;		//�Ƿ��ȡ��GPS����
	char isParseData;	//�Ƿ�������
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char raw_latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char raw_longitude[longitude_Length];		//����
	char E_W[E_W_Length];		//E/W
	char knot[knot_length];//���ٶ�
	char isUsefull;		//��λ��Ϣ�Ƿ���Ч
	float latitude;
	float longitude;
	float speed;
} GPSData;

extern uint8_t GPS_Frame[USART_REC_LEN];
extern uint8_t GPS_data;

extern GPSData GPS;

void parseGpsBuffer(void);
void gcj02_to_wgs84(double lon, double lat, double *output);
#endif

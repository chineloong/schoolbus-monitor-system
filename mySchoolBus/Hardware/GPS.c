#include "GPS.h"
#include "string.h"
#include "math.h"
#include "GPS_Transform.h"


extern UART_HandleTypeDef huart1;

uint8_t GPS_Frame[USART_REC_LEN];
uint8_t GPS_data;

GPSData GPS;

//GPS���ݽ���
float mylatitude,mylongitude;
void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (GPS.isGetData)
	{
		GPS.isGetData = false;
		
		for (i = 0 ; i <= 7 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(GPS.GPS_Buffer, ",")) == NULL);
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(GPS.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 3:memcpy(GPS.raw_latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(GPS.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(GPS.raw_longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(GPS.E_W, subString, subStringNext - subString);break;	//��ȡE/W
						case 7:memcpy(GPS.knot, subString, subStringNext - subString);break;	//��ȡE/W

						default:break;
					}
					
					int degrees,minutes;
					float seconds;
					
					// ���ַ����ָ�Ϊ�ȡ��֡���
					degrees = (GPS.raw_latitude[0] - '0') * 10 + (GPS.raw_latitude[1] - '0'); // ��
					minutes = (GPS.raw_latitude[2] - '0') * 10 + (GPS.raw_latitude[3] - '0'); // ��
					sscanf(GPS.raw_latitude, "%f", &mylatitude);
					seconds = mylatitude - (int)mylatitude;
					mylatitude = degrees + minutes / 60.0f + seconds / 60.0f;
					
					
					
					// ���ַ����ָ�Ϊ�ȡ��֡���
					degrees = (GPS.raw_longitude[0] - '0') * 100 + (GPS.raw_longitude[1] - '0')*10 + (GPS.raw_longitude[2] - '0'); // ��
					minutes = (GPS.raw_longitude[3] - '0') * 10 + (GPS.raw_longitude[4] - '0'); // ��
					sscanf(GPS.raw_longitude, "%f", &mylongitude);
					seconds = mylongitude - (int)mylongitude;
					mylongitude = degrees + minutes / 60.0f + seconds / 60.0f;
					
					
					GPS.latitude = mylatitude;
					GPS.longitude = mylongitude; 
					
					wgs84togcj02(&GPS.longitude,&GPS.latitude);
					
					sscanf(GPS.knot, "%f", &GPS.speed);
					GPS.speed = GPS.speed/1.852f;
					
					subString = subStringNext;
					GPS.isParseData = true;
					if(usefullBuffer[0] == 'A')
						GPS.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						GPS.isUsefull = false;

				}
				else
				{
				}
			}


		}
	}
}


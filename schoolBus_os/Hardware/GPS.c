#include "GPS.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart1;

uint8_t GPS_Frame[USART_REC_LEN];
uint8_t GPS_data;

GPSData GPS;

//GPS数据解算
float mylatitude,mylongitude;

/**
 * @description: 
 * @param {float} lng
 * @param {float} lat
 * @return {*}
 */
float transformlat(float lng, float lat)
{
    float ret = -100.0f + 2.0f * lng + 3.0f * lat + 0.2f * lat * lat + \
        0.1f * lng * lat + 0.2f * sqrt(abs(lng));

    ret += (20.0f * sin(6.0f * lng * pi) + 20.0f *
            sin(2.0f * lng * pi)) * 2.0f / 3.0f;

    ret += (20.0f * sin(lat * pi) + 40.0f *
            sin(lat / 3.0f * pi)) * 2.0f / 3.0f;

    ret += (160.0f * sin(lat / 12.0f * pi) + 320 *
            sin(lat * pi / 30.0f)) * 2.0f / 3.0f;

    return ret;
}
 
float transformlng(float lng, float lat)
{
    float ret = 300.0f + lng + 2.0f * lat + 0.1f * lng * lng + \
        0.1f * lng * lat + 0.1f * sqrt(abs(lng));

    ret += (20.0f * sin(6.0f * lng * pi) + 20.0f *
            sin(2.0f * lng * pi)) * 2.0f / 3.0f;

    ret += (20.0f * sin(lng * pi) + 40.0f *
            sin(lng / 3.0f * pi)) * 2.0f / 3.0f;

    ret += (150.0f * sin(lng / 12.0f * pi) + 300.0f *
            sin(lng / 30.0f * pi)) * 2.0f / 3.0f;

    return ret;
}
 
 
/// @brief WGS84转GCJ02(火星坐标系)
/// @param lng 
/// @param lat 
void wgs84togcj02(float *lng, float *lat)
{
    // """
    // WGS84转GCJ02(火星坐标系)
    // :param lng:WGS84坐标系的经度
    // :param lat:WGS84坐标系的纬度
    // :return:
    // """
    float dlat = transformlat(*lng - 105.0f, *lat - 35.0f);
    float dlng = transformlng(*lng - 105.0f, *lat - 35.0f);
    float radlat = *lat / 180.0f * pi;
    float magic = sin(radlat);
    magic = 1 - ee * magic * magic;
    float sqrtmagic = sqrt(magic);
    dlat = (dlat * 180.0f) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi);
    dlng = (dlng * 180.0f) / (a / sqrtmagic * cos(radlat) * pi);
    float mglat = *lat + dlat;
    float mglng = *lng + dlng;

	*lat = mglat;
	*lng = mglng;
}

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
						case 1:memcpy(GPS.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(GPS.raw_latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(GPS.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(GPS.raw_longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(GPS.E_W, subString, subStringNext - subString);break;	//获取E/W
						case 7:memcpy(GPS.knot, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}
					
					int degrees,minutes;
					float seconds;
					
					// 将字符串分割为度、分、秒
					degrees = (GPS.raw_latitude[0] - '0') * 10 + (GPS.raw_latitude[1] - '0'); // 度
					minutes = (GPS.raw_latitude[2] - '0') * 10 + (GPS.raw_latitude[3] - '0'); // 分
					sscanf(GPS.raw_latitude, "%f", &mylatitude);
					seconds = mylatitude - (int)mylatitude;
					mylatitude = degrees + minutes / 60.0f + seconds / 60.0f;
					
					
					
					// 将字符串分割为度、分、秒
					degrees = (GPS.raw_longitude[0] - '0') * 100 + (GPS.raw_longitude[1] - '0')*10 + (GPS.raw_longitude[2] - '0'); // 度
					minutes = (GPS.raw_longitude[3] - '0') * 10 + (GPS.raw_longitude[4] - '0'); // 分
					sscanf(GPS.raw_longitude, "%f", &mylongitude);
					seconds = mylongitude - (int)mylongitude;
					mylongitude = degrees + minutes / 60.0f + seconds / 60.0f;
					
					
					GPS.latitude = mylatitude;
					GPS.longitude = mylongitude; 
					
                    //坐标转换
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

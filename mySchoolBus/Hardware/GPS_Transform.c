#include "stdio.h"
#include "math.h"
#include "GPS_Transform.h"

#define x_pi  3.14159265358979324 * 3000.0 / 180.0
#define pi  3.1415926535897932384626  // π
#define a  6378245.0  //长半轴
#define ee  0.00669342162296594323  //扁率
 
float transformlng(float lng, float lat);
float transformlat(float lng, float lat);
 
void wgs84togcj02(float *lng, float *lat)
{
    // """
    // WGS84转GCJ02(火星坐标系)
    // :param lng:WGS84坐标系的经度
    // :param lat:WGS84坐标系的纬度
    // :return:
    // """
    float dlat = transformlat(*lng - 105.0, *lat - 35.0);
    float dlng = transformlng(*lng - 105.0, *lat - 35.0);
    float radlat = *lat / 180.0 * pi;
    float magic = sin(radlat);
    magic = 1 - ee * magic * magic;
    float sqrtmagic = sqrt(magic);
    dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi);
    dlng = (dlng * 180.0) / (a / sqrtmagic * cos(radlat) * pi);
    float mglat = *lat + dlat;
    float mglng = *lng + dlng;

	*lat = mglat;
	*lng = mglng;
}

 
 
float transformlat(float lng, float lat)
{
    float ret = -100.0f + 2.0f * lng + 3.0f * lat + 0.2f * lat * lat + \
        0.1f * lng * lat + 0.2f * sqrt(abs(lng));

    ret += (20.0f * sin(6.0 * lng * pi) + 20.0f *
            sin(2.0 * lng * pi)) * 2.0f / 3.0f;

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
 

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
    float ret = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + \
        0.1 * lng * lat + 0.2 * sqrt(abs(lng));

    ret += (20.0 * sin(6.0 * lng * pi) + 20.0 *
            sin(2.0 * lng * pi)) * 2.0 / 3.0;

    ret += (20.0 * sin(lat * pi) + 40.0 *
            sin(lat / 3.0 * pi)) * 2.0 / 3.0;

    ret += (160.0 * sin(lat / 12.0 * pi) + 320 *
            sin(lat * pi / 30.0)) * 2.0 / 3.0;

    return ret;
}
 
float transformlng(float lng, float lat)
{
    float ret = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + \
        0.1 * lng * lat + 0.1 * sqrt(abs(lng));

    ret += (20.0 * sin(6.0 * lng * pi) + 20.0 *
            sin(2.0 * lng * pi)) * 2.0 / 3.0;

    ret += (20.0 * sin(lng * pi) + 40.0 *
            sin(lng / 3.0 * pi)) * 2.0 / 3.0;

    ret += (150.0 * sin(lng / 12.0 * pi) + 300.0 *
            sin(lng / 30.0 * pi)) * 2.0 / 3.0;

    return ret;
}
 

#include "stm32f4xx.h"
#include "4G.h"
#include "GPS.h"
#include "atk_idm750c_cfg.h"
#include "atk_idm750c_uart.h"
#include "atk_idm750c.h"
#include "stdio.h"

extern UART_HandleTypeDef huart3;
extern GPSData GPS;

void Net4GInit(void)
{
		//配置参数
		atk_idm750c_init(0);
		 /* ATK-IDM750C AT指令测试 */
		atk_idm750c_at_test();
		/* ATK-IDM750C 工作模式设置 */
		atk_idm750c_query_workmode(ATK_IDM750C_WORKMODE_HTTP);
		//配置PostURL
		atk_idm750c_http_url_address("http://101.32.36.52:6666/post");
		//HTTP模式设定	
		atk_idm750c_http_request_mode(ATK_IDM750C_HTTP_REQUEST_POST);
		//时间
		atk_idm750c_http_request_timeout();
		//进入透传模式
		atk_idm750c_enter_transfermode();

}

//发送到云端的数据
void Message_Send(char * msg,int length)
{

		HAL_UART_Transmit(&huart3,(uint8_t *)msg,length,100);

}

//发送GPS数据
void GPS_Send(void)
{
		char msg[100];
		int size;
		if(1)//GPS.isUsefull
		{
				//sprintf(msg,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
				size = snprintf(msg,100,"!%f,%f,%f",140.2f,300.8f,3.5f);
				Message_Send(msg,size);

		}

}

//发送学生ID
void studentID_Send(uint32_t ID)
{
		char msg[100];
		sprintf(msg,"!%f,%f,%f",GPS.latitude,GPS.longitude,GPS.speed);
		Message_Send(msg,50);
}

void DangerousDriving_Send(int type)
{
		char msg[100];
		sprintf(msg,"#%d",type);
		Message_Send(msg,50);

}
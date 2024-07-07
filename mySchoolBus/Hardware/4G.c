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
		//���ò���
		atk_idm750c_init(0);
		 /* ATK-IDM750C ATָ����� */
		atk_idm750c_at_test();
		/* ATK-IDM750C ����ģʽ���� */
		atk_idm750c_query_workmode(ATK_IDM750C_WORKMODE_HTTP);
		//����PostURL
		atk_idm750c_http_url_address("http://101.32.36.52:6666/post");
		//HTTPģʽ�趨	
		atk_idm750c_http_request_mode(ATK_IDM750C_HTTP_REQUEST_POST);
		//ʱ��
		atk_idm750c_http_request_timeout();
		//����͸��ģʽ
		atk_idm750c_enter_transfermode();

}

//���͵��ƶ˵�����
void Message_Send(char * msg,int length)
{

		HAL_UART_Transmit(&huart3,(uint8_t *)msg,length,100);

}

//����GPS����
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

//����ѧ��ID
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
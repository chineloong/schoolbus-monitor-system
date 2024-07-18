#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "4G.h"

extern UART_HandleTypeDef huart4;

// �������ָ�����ݵı�־λ
int config_flag = 0;

// ���崮��1�ķ��ͺͽ��ջ�����
char txBuffer[TX_BUFFER_SIZE];
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxData;
char receiveData[RX_BUFFER_SIZE];

const char ack[]="\r\nOK\r\n\r\n";
const char config_head[]="+++";
const char config_reply[]="a";
const char netmode[]="AT+WKMOD=HTTPD\r\n";
const char httpmode[]="AT+HTPTP=POST\r\n";
const char httpurl[]="AT+HTPURL=http://101.32.36.52:8088/post\r\n";
const char httpserver[]="AT+HTPSV=101.32.36.52,8088\r\n";
const char http_response[]="AT+HTPHD=Connection: close[0D][0A]\r\n";
const char http_time[]="AAT+HTPTO=10\r\n";
const char Restart[]="AT+Z\r\n";
const char Transmit[]="AT+ENTM\r\n";

// ���ڷ������ݺ���const char *
void Net_send(const char* data) 
{
    // ��Ҫ���͵����ݿ��������ͻ�����
    strncpy(txBuffer, data, TX_BUFFER_SIZE);
    // ����HAL�⺯����������
    HAL_UART_Transmit(&huart4, (uint8_t*)txBuffer, strlen(txBuffer), HAL_MAX_DELAY);
}

/**
 * @description: ��������ģʽ
 * @return {*}
 */
void NetConfigMode(void)
{
		
		Net_send(config_head);
	
		while(strcmp(receiveData, "a") != 0)
		{
		};
		HAL_Delay(500);
		HAL_UART_Transmit(&huart4, (uint8_t *)config_reply, 1, HAL_MAX_DELAY);
		while(strcmp(receiveData, "+ok\r\n") != 0)
		{
		};
		HAL_Delay(500);

}

void NetTransformMode(void)
{
		char str[100];
		Net_send(Transmit);
		sprintf(str,"%s%s",netmode,ack);sprintf(str,"%s%s",netmode,ack);
		while(strcmp(receiveData,str) != 0)
		{
		};

}
/**
 * @description: ����
 * @return {*}
 */
void NetRestart(void)
{

		HAL_UART_Transmit(&huart4, (uint8_t *)Restart, strlen(Restart), HAL_MAX_DELAY);
		while(strcmp(receiveData, ack) != 0)
		{
		};
		while(strcmp(receiveData, "\r\n[WH-LTE-7S4 V2]\r\n") != 0)
		{
		};
}

//ʹ�ô��ڽ��յ����ݽ����жϣ�������+++ʱ���ȴ�����atk��Ȼ����atkȻ���������
void Net_Config(void)
{	
		HAL_UART_Receive_IT(&huart4,(uint8_t *)&rxData,1);
		HAL_Delay(100);
	
		Net_send(Transmit);
		HAL_Delay(500);

		char str[100];
		
    // �жϽ��յ��������Ƿ�Ϊָ������
    if(config_flag == 0)
    {
				NetConfigMode();
        config_flag = 1;
		}
    if(config_flag == 1)
    {	
        // ���ý��ձ�־λΪtrue
        config_flag = 2;
				memset(receiveData,0,RX_BUFFER_SIZE);
				HAL_UART_Transmit(&huart4, (uint8_t *)netmode, strlen(netmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 2)
    {
				//sprintf(str,"%s%s",netmode,ack);
				while(strcmp(receiveData,ack) != 0)
				{
				};
        // ���ý��ձ�־λΪtrue
        config_flag = 3;
				memset(receiveData,0,RX_BUFFER_SIZE);
				HAL_UART_Transmit(&huart4, (uint8_t *)httpmode, strlen(httpmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 3)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 4;
				memset(receiveData,0,RX_BUFFER_SIZE);
				HAL_UART_Transmit(&huart4, (uint8_t *)httpurl, strlen(httpurl), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 4)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λ-Ϊtrue
        config_flag = 5;
				HAL_UART_Transmit(&huart4, (uint8_t *)httpserver, strlen(httpserver), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 5)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λ-Ϊtrue
        config_flag = 6;
				HAL_UART_Transmit(&huart4, (uint8_t *)http_response, strlen(http_response), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 6)
    {
				while(strcmp(receiveData,ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 7;
				NetRestart();
    }
}



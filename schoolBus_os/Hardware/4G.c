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

const char ack[]="\r\nOK\r\n";
const char config_head[]="+++";
const char config_reply[]="atk";
const char netmode[]="AT+WORK=\"HTTP\"\r\n";
const char httpmode[]="AT+HTTPMD=\"POST\"\r\n";
const char httpurl[]="AT+HTTPURL=\"http://101.32.36.52:8088/post\"\r\n";
const char http_response[]="AT+HTTPHD=\"Connection:close\"\r\n";
const char http_time[]="AT+HTTPTM=\"10\"\r\n";
const char ATO[]="ATO\r\n";

// ���ڷ������ݺ���
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
		while(strcmp(receiveData, "atk") != 0)
				{
				};
		// ���ý��ձ�־λΪtrue
		HAL_Delay(500);
		HAL_UART_Transmit(&huart4, (uint8_t *)config_reply, 3, HAL_MAX_DELAY);
		HAL_Delay(500);

}
/**
 * @description: ����͸��ģʽ
 * @return {*}
 */
void NetTransformMode(void)
{

		HAL_UART_Transmit(&huart4, (uint8_t *)ATO, strlen(ATO), HAL_MAX_DELAY);
		HAL_Delay(300);

}

//ʹ�ô��ڽ��յ����ݽ����жϣ�������+++ʱ���ȴ�����atk��Ȼ����atkȻ���������
void Net_Config(void)
{	
		HAL_UART_Receive_IT(&huart4,(uint8_t *)&rxData,1);
		HAL_Delay(100);
	
		NetTransformMode();
		HAL_Delay(300);

		
    // �жϽ��յ��������Ƿ�Ϊָ������
    if(config_flag == 0)
    {
				NetConfigMode();
        config_flag = 1;
		}
    if(config_flag == 1)
    {	
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 2;
				HAL_UART_Transmit(&huart4, (uint8_t *)netmode, strlen(netmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 2)
    {
				while(strcmp(receiveData,ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 3;
				HAL_UART_Transmit(&huart4, (uint8_t *)httpmode, strlen(httpmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 3)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 4;
				HAL_UART_Transmit(&huart4, (uint8_t *)httpurl, strlen(httpurl), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 4)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 5;
				HAL_UART_Transmit(&huart4, (uint8_t *)http_response, strlen(http_response), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 5)
    {
				while(strcmp(receiveData,ack) != 0)
				{};
        // ���ý��ձ�־λΪtrue
        config_flag = 6;
				NetTransformMode();
    }
}



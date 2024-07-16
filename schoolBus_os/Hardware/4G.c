#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "4G.h"

extern UART_HandleTypeDef huart4;

// 定义接收指定数据的标志位
int config_flag = 0;

// 定义串口1的发送和接收缓冲区
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

// 串口发送数据函数
void Net_send(const char* data) 
{
    // 将要发送的数据拷贝到发送缓冲区
    strncpy(txBuffer, data, TX_BUFFER_SIZE);
    // 调用HAL库函数发送数据
    HAL_UART_Transmit(&huart4, (uint8_t*)txBuffer, strlen(txBuffer), HAL_MAX_DELAY);
}

/**
 * @description: 进入配置模式
 * @return {*}
 */
void NetConfigMode(void)
{

		Net_send(config_head);
		while(strcmp(receiveData, "atk") != 0)
				{
				};
		// 设置接收标志位为true
		HAL_Delay(500);
		HAL_UART_Transmit(&huart4, (uint8_t *)config_reply, 3, HAL_MAX_DELAY);
		HAL_Delay(500);

}
/**
 * @description: 进入透传模式
 * @return {*}
 */
void NetTransformMode(void)
{

		HAL_UART_Transmit(&huart4, (uint8_t *)ATO, strlen(ATO), HAL_MAX_DELAY);
		HAL_Delay(300);

}

//使用串口接收的数据进行判断，当发送+++时，等待返回atk，然后发送atk然后进行配置
void Net_Config(void)
{	
		HAL_UART_Receive_IT(&huart4,(uint8_t *)&rxData,1);
		HAL_Delay(100);
	
		NetTransformMode();
		HAL_Delay(300);

		
    // 判断接收到的数据是否为指定数据
    if(config_flag == 0)
    {
				NetConfigMode();
        config_flag = 1;
		}
    if(config_flag == 1)
    {	
				while(strcmp(receiveData, ack) != 0)
				{};
        // 设置接收标志位为true
        config_flag = 2;
				HAL_UART_Transmit(&huart4, (uint8_t *)netmode, strlen(netmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 2)
    {
				while(strcmp(receiveData,ack) != 0)
				{};
        // 设置接收标志位为true
        config_flag = 3;
				HAL_UART_Transmit(&huart4, (uint8_t *)httpmode, strlen(httpmode), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 3)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // 设置接收标志位为true
        config_flag = 4;
				HAL_UART_Transmit(&huart4, (uint8_t *)httpurl, strlen(httpurl), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 4)
    {
				while(strcmp(receiveData, ack) != 0)
				{};
        // 设置接收标志位为true
        config_flag = 5;
				HAL_UART_Transmit(&huart4, (uint8_t *)http_response, strlen(http_response), HAL_MAX_DELAY);
        HAL_Delay(300);
    }
		if(config_flag == 5)
    {
				while(strcmp(receiveData,ack) != 0)
				{};
        // 设置接收标志位为true
        config_flag = 6;
				NetTransformMode();
    }
}



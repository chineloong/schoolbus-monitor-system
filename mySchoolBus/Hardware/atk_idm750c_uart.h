/**
 ****************************************************************************************************
 * @file        atk_idm750c_uart.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK_IDM750Cģ��UART�ӿ���������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_IDM750C_UART_H
#define __ATK_IDM750C_UART_H

#include "stm32f4xx.h"

/* ���Ŷ��� */
#define ATK_IDM750C_UART_TX_GPIO_PORT         GPIOB
#define ATK_IDM750C_UART_TX_GPIO_PIN          GPIO_PIN_10
#define ATK_IDM750C_UART_TX_GPIO_AF           GPIO_AF7_USART3
#define ATK_IDM750C_UART_TX_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define ATK_IDM750C_UART_RX_GPIO_PORT         GPIOB
#define ATK_IDM750C_UART_RX_GPIO_PIN          GPIO_PIN_11
#define ATK_IDM750C_UART_RX_GPIO_AF           GPIO_AF7_USART3
#define ATK_IDM750C_UART_RX_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define ATK_IDM750C_UART_INTERFACE            USART3
#define ATK_IDM750C_UART_IRQn                 USART3_IRQn

#define ATK_IDM750C_UART_CLK_ENABLE()         do{ __HAL_RCC_USART3_CLK_ENABLE(); }while(0)

/* UART�շ������С */
#define ATK_IDM750C_UART_RX_BUF_SIZE          1024
#define ATK_IDM750C_UART_TX_BUF_SIZE          512

/* �������� */
void atk_idm750c_uart_printf(char *fmt, ...);           /* ATK-IDM750C UART printf */
void atk_idm750c_uart_rx_restart(void);                 /* ATK-IDM750C UART���¿�ʼ�������� */
uint8_t *atk_idm750c_uart_rx_get_frame(void);           /* ��ȡATK-IDM750C UART���յ���һ֡���� */
uint16_t atk_idm750c_uart_rx_get_frame_len(void);       /* ��ȡATK-IDM750C UART���յ���һ֡���ݵĳ��� */
void atk_idm750c_uart_init(uint32_t baudrate);          /* ATK-IDM750C UART��ʼ�� */
void ATK_IDM750C_UART_IRQHandler(void);
#endif

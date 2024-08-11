/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Net_Tx_Pin GPIO_PIN_0
#define Net_Tx_GPIO_Port GPIOA
#define Net_Rx_Pin GPIO_PIN_1
#define Net_Rx_GPIO_Port GPIOA
#define BLE_Tx_Pin GPIO_PIN_2
#define BLE_Tx_GPIO_Port GPIOA
#define BLE_Rx_Pin GPIO_PIN_3
#define BLE_Rx_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LCD_LED_Pin GPIO_PIN_4
#define LCD_LED_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_5
#define LCD_RS_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_0
#define LCD_RST_GPIO_Port GPIOB
#define NFC_Tx_Pin GPIO_PIN_10
#define NFC_Tx_GPIO_Port GPIOB
#define NFC_Rx_Pin GPIO_PIN_11
#define NFC_Rx_GPIO_Port GPIOB
#define GPS_Tx_Pin GPIO_PIN_9
#define GPS_Tx_GPIO_Port GPIOA
#define GPS_Rx_Pin GPIO_PIN_10
#define GPS_Rx_GPIO_Port GPIOA
#define SpeakTx_Pin GPIO_PIN_12
#define SpeakTx_GPIO_Port GPIOC
#define check1_Pin GPIO_PIN_0
#define check1_GPIO_Port GPIOD
#define check1_EXTI_IRQn EXTI0_IRQn
#define check2_Pin GPIO_PIN_1
#define check2_GPIO_Port GPIOD
#define check2_EXTI_IRQn EXTI1_IRQn
#define SpeakRx_Pin GPIO_PIN_2
#define SpeakRx_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

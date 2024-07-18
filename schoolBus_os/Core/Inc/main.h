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
#define supersonic_echo_Pin GPIO_PIN_9
#define supersonic_echo_GPIO_Port GPIOE
#define superrsonic_tirgger_Pin GPIO_PIN_10
#define superrsonic_tirgger_GPIO_Port GPIOE
#define supersonic2_echo_Pin GPIO_PIN_11
#define supersonic2_echo_GPIO_Port GPIOE
#define superrsonic2_tirgger_Pin GPIO_PIN_12
#define superrsonic2_tirgger_GPIO_Port GPIOE
#define NFC_Tx_Pin GPIO_PIN_10
#define NFC_Tx_GPIO_Port GPIOB
#define NFC_Rx_Pin GPIO_PIN_11
#define NFC_Rx_GPIO_Port GPIOB
#define GPS_Tx_Pin GPIO_PIN_9
#define GPS_Tx_GPIO_Port GPIOA
#define GPS_Rx_Pin GPIO_PIN_10
#define GPS_Rx_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

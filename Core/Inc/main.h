/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define ENCODER1A_PIN_Pin GPIO_PIN_0
#define ENCODER1A_PIN_GPIO_Port GPIOA
#define ENCODER1B_PIN_Pin GPIO_PIN_1
#define ENCODER1B_PIN_GPIO_Port GPIOA
#define TX3_PIN_Pin GPIO_PIN_2
#define TX3_PIN_GPIO_Port GPIOA
#define RX3_PIN_Pin GPIO_PIN_3
#define RX3_PIN_GPIO_Port GPIOA
#define POT_PIN_Pin GPIO_PIN_4
#define POT_PIN_GPIO_Port GPIOA
#define INT_PIN_Pin GPIO_PIN_5
#define INT_PIN_GPIO_Port GPIOA
#define ENCODER2A_PIN_Pin GPIO_PIN_6
#define ENCODER2A_PIN_GPIO_Port GPIOA
#define ENCODER2B_PIN_Pin GPIO_PIN_7
#define ENCODER2B_PIN_GPIO_Port GPIOA
#define ADC_TOP_Pin GPIO_PIN_0
#define ADC_TOP_GPIO_Port GPIOB
#define ADC_BOTTOM_Pin GPIO_PIN_1
#define ADC_BOTTOM_GPIO_Port GPIOB
#define EXTI1_PIN_Pin GPIO_PIN_2
#define EXTI1_PIN_GPIO_Port GPIOB
#define MULPLXA_PIN_Pin GPIO_PIN_10
#define MULPLXA_PIN_GPIO_Port GPIOB
#define MULPLXB_PIN_Pin GPIO_PIN_12
#define MULPLXB_PIN_GPIO_Port GPIOB
#define MULPLXC_PIN_Pin GPIO_PIN_13
#define MULPLXC_PIN_GPIO_Port GPIOB
#define BTN1_DIR_PIN_Pin GPIO_PIN_14
#define BTN1_DIR_PIN_GPIO_Port GPIOB
#define BTN2_DIR_PIN_Pin GPIO_PIN_15
#define BTN2_DIR_PIN_GPIO_Port GPIOB
#define BTN2_PWM_PIN_Pin GPIO_PIN_8
#define BTN2_PWM_PIN_GPIO_Port GPIOA
#define BTN1_PWM_PIN_Pin GPIO_PIN_9
#define BTN1_PWM_PIN_GPIO_Port GPIOA
#define LED_PIN_Pin GPIO_PIN_10
#define LED_PIN_GPIO_Port GPIOA
#define EXTI5_PIN_Pin GPIO_PIN_15
#define EXTI5_PIN_GPIO_Port GPIOA
#define EXTI2_PIN_Pin GPIO_PIN_3
#define EXTI2_PIN_GPIO_Port GPIOB
#define EXTI3_PIN_Pin GPIO_PIN_4
#define EXTI3_PIN_GPIO_Port GPIOB
#define TX2_PIN_Pin GPIO_PIN_6
#define TX2_PIN_GPIO_Port GPIOB
#define RX2_PIN_Pin GPIO_PIN_7
#define RX2_PIN_GPIO_Port GPIOB
#define II2C_SCL_PIN_Pin GPIO_PIN_8
#define II2C_SCL_PIN_GPIO_Port GPIOB
#define I2C_SDA_PIN_Pin GPIO_PIN_9
#define I2C_SDA_PIN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define RGB_GPIO_Port GPIOC

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RGB_B_Pin GPIO_PIN_13
#define RGB_B_GPIO_Port GPIOC
#define RGB_G_Pin GPIO_PIN_14
#define RGB_G_GPIO_Port GPIOC
#define RGB_R_Pin GPIO_PIN_15
#define RGB_R_GPIO_Port GPIOC
#define LASER_CTL_Pin GPIO_PIN_0
#define LASER_CTL_GPIO_Port GPIOA
#define IR_DATA_OUT_Pin GPIO_PIN_1
#define IR_DATA_OUT_GPIO_Port GPIOA
#define IR_PWM_OUT_Pin GPIO_PIN_2
#define IR_PWM_OUT_GPIO_Port GPIOA
#define AUDIO_ENABLE_Pin GPIO_PIN_0
#define AUDIO_ENABLE_GPIO_Port GPIOB
#define TEAM_SEL_Pin GPIO_PIN_10
#define TEAM_SEL_GPIO_Port GPIOB
#define TEAM_SEL_EXTI_IRQn EXTI4_15_IRQn
#define TRIGGER_Pin GPIO_PIN_11
#define TRIGGER_GPIO_Port GPIOB
#define TRIGGER_EXTI_IRQn EXTI4_15_IRQn
#define SPIFLASH_NSS_Pin GPIO_PIN_12
#define SPIFLASH_NSS_GPIO_Port GPIOB
#define WEAPON_SEL_FW_Pin GPIO_PIN_6
#define WEAPON_SEL_FW_GPIO_Port GPIOB
#define WEAPON_SEL_FW_EXTI_IRQn EXTI4_15_IRQn
#define WEAPON_SEL_BW_Pin GPIO_PIN_7
#define WEAPON_SEL_BW_GPIO_Port GPIOB
#define WEAPON_SEL_BW_EXTI_IRQn EXTI4_15_IRQn
#define IR_DATA_IN_Pin GPIO_PIN_9
#define IR_DATA_IN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

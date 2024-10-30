/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "gpio.h"
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for mainThread */
osThreadId_t mainThreadHandle;
const osThreadAttr_t mainThread_attributes = {
  .name = "mainThread",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ButtonThread */
osThreadId_t ButtonThreadHandle;
const osThreadAttr_t ButtonThread_attributes = {
  .name = "ButtonThread",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void osMainThread(void *argument);
void osButtonThread(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of mainThread */
  mainThreadHandle = osThreadNew(osMainThread, NULL, &mainThread_attributes);

  /* creation of ButtonThread */
  ButtonThreadHandle = osThreadNew(osButtonThread, NULL, &ButtonThread_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_osMainThread */
/**
  * @brief  Function implementing the mainThread thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_osMainThread */
void osMainThread(void *argument)
{
  /* USER CODE BEGIN osMainThread */
  /* Infinite loop */
	osThreadSuspend(mainThreadHandle);
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END osMainThread */
}

/* USER CODE BEGIN Header_osButtonThread */
/**
* @brief Function implementing the ButtonThread thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_osButtonThread */
void osButtonThread(void *argument)
{
  /* USER CODE BEGIN osButtonThread */
  /* Infinite loop */
	osThreadSuspend(ButtonThreadHandle);
  for(;;)
  {
	  HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_1);
	  osDelay(500);
	  HAL_TIM_OC_Stop(&htim3, TIM_CHANNEL_1);
	  osDelay(500);
  }
  /* USER CODE END osButtonThread */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


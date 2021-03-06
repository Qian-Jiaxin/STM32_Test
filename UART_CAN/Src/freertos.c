/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
// #include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "cmsis_os2.h"
#include "slip_exchange.h"
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for Task_UART2CAN */
osThreadId_t Task_UART2CANHandle;
const osThreadAttr_t Task_UART2CAN_attributes = {
  .name = "Task_UART2CAN",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_CAN2UART */
osThreadId_t Task_CAN2UARTHandle;
const osThreadAttr_t Task_CAN2UART_attributes = {
  .name = "Task_CAN2UART",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Queue_CAN */
osMessageQueueId_t Queue_CANHandle;
const osMessageQueueAttr_t Queue_CAN_attributes = {
  .name = "Queue_CAN"
};
/* Definitions for Queue_UART */
osMessageQueueId_t Queue_UARTHandle;
const osMessageQueueAttr_t Queue_UART_attributes = {
  .name = "Queue_UART"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask_UART2CAN(void *argument);
void StartTask_CAN2UART(void *argument);

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

  /* Create the queue(s) */
  /* creation of Queue_CAN */
  Queue_CANHandle = osMessageQueueNew (8, sizeof(uint8_t), &Queue_CAN_attributes);

  /* creation of Queue_UART */
  Queue_UARTHandle = osMessageQueueNew (8, sizeof(uint8_t), &Queue_UART_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task_UART2CAN */
  Task_UART2CANHandle = osThreadNew(StartTask_UART2CAN, NULL, &Task_UART2CAN_attributes);

  /* creation of Task_CAN2UART */
  Task_CAN2UARTHandle = osThreadNew(StartTask_CAN2UART, NULL, &Task_CAN2UART_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask_UART2CAN */
/**
* @brief Function implementing the Task_UART2CAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_UART2CAN */
void StartTask_UART2CAN(void *argument)
{
  /* USER CODE BEGIN StartTask_UART2CAN */
  slip_decode_t slip_decode;
  uint8_t queue_rec[10] = {0};
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    if(osMessageQueueGet(Queue_UARTHandle, queue_rec, NULL, osWaitForever) == osOK)
    {
      memcpy(&slip_decode.uart_array, queue_rec, 10);
      if(uart_to_can(&slip_decode) == -1)
      {
        //TODO
      }
    }
  }
  /* USER CODE END StartTask_UART2CAN */
}

/* USER CODE BEGIN Header_StartTask_CAN2UART */
/**
* @brief Function implementing the Task_CAN2UART thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_CAN2UART */
void StartTask_CAN2UART(void *argument)
{
  /* USER CODE BEGIN StartTask_CAN2UART */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask_CAN2UART */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

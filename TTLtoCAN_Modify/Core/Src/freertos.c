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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
osThreadId Task_CANtoUARTHandle;
osThreadId Task_UARTtoCANHandle;
osMessageQId Queue_CANtoUARTHandle;
osMessageQId Queue_UARTtoCANHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask_CANtoUART(void const * argument);
void StartTask_UARTtoCAN(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of Queue_CANtoUART */
  osMessageQDef(Queue_CANtoUART, 48, uint8_t);
  Queue_CANtoUARTHandle = osMessageCreate(osMessageQ(Queue_CANtoUART), NULL);

  /* definition and creation of Queue_UARTtoCAN */
  osMessageQDef(Queue_UARTtoCAN, 100, uint8_t);
  Queue_UARTtoCANHandle = osMessageCreate(osMessageQ(Queue_UARTtoCAN), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_CANtoUART */
  osThreadDef(Task_CANtoUART, StartTask_CANtoUART, osPriorityNormal, 0, 128);
  Task_CANtoUARTHandle = osThreadCreate(osThread(Task_CANtoUART), NULL);

  /* definition and creation of Task_UARTtoCAN */
  osThreadDef(Task_UARTtoCAN, StartTask_UARTtoCAN, osPriorityNormal, 0, 128);
  Task_UARTtoCANHandle = osThreadCreate(osThread(Task_UARTtoCAN), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask_CANtoUART */
/**
  * @brief  Function implementing the Task_CANtoUART thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask_CANtoUART */
void StartTask_CANtoUART(void const * argument)
{
  /* USER CODE BEGIN StartTask_CANtoUART */
  osEvent event_CANtoUART;
  uint8_t *p = NULL;
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    event_CANtoUART = osMessageGet(Queue_CANtoUARTHandle, osWaitForever);
    if(event_CANtoUART.status == osEventMessage)
    {
      p = (uint8_t *)event_CANtoUART.value.p;
    }
  }
  /* USER CODE END StartTask_CANtoUART */
}

/* USER CODE BEGIN Header_StartTask_UARTtoCAN */
/**
* @brief Function implementing the Task_UARTtoCAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_UARTtoCAN */
void StartTask_UARTtoCAN(void const * argument)
{
  /* USER CODE BEGIN StartTask_UARTtoCAN */
  osEvent event_UARTtoCAN;
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    event_UARTtoCAN = osMessageGet(Queue_UARTtoCANHandle, osWaitForever);
    if(event_UARTtoCAN.status == osEventMessage)
    {

    }
  }
  /* USER CODE END StartTask_UARTtoCAN */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

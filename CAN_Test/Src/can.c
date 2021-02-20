/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 9;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void myCAN_Init(void)
{
  extern CAN_TxHeaderTypeDef CAN_TxHeaderStruct;
  CAN_TxHeaderStruct.IDE = CAN_ID_STD;
  CAN_TxHeaderStruct.RTR = CAN_RTR_DATA;
  CAN_TxHeaderStruct.StdId = 0x0;
  CAN_TxHeaderStruct.ExtId = 0x0;
  CAN_TxHeaderStruct.DLC = 8;
  CAN_TxHeaderStruct.TransmitGlobalTime = DISABLE;

  // extern CAN_RxHeaderTypeDef CAN_RxHeaderStruct;
  // CAN_RxHeaderStruct.IDE = CAN_ID_STD;
  // CAN_RxHeaderStruct.RTR = CAN_RTR_DATA;
  // CAN_RxHeaderStruct.StdId = 0x0;
  // CAN_RxHeaderStruct.ExtId = 0x0;
  // CAN_RxHeaderStruct.DLC = 8;
  // CAN_RxHeaderStruct.FilterMatchIndex = ;
  // CAN_RxHeaderStruct.Timestamp = 100;

  CAN_FilterTypeDef CAN_FilterStruct;
  CAN_FilterStruct.FilterBank = 0;
  CAN_FilterStruct.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN_FilterStruct.FilterIdHigh = 0x0001;
  CAN_FilterStruct.FilterIdLow = 0x0002;
  CAN_FilterStruct.FilterMaskIdHigh = 0x0003;
  CAN_FilterStruct.FilterMaskIdLow = 0x0004;
  // CAN_FilterStruct.SlaveStartFilterBank = 3;
  CAN_FilterStruct.FilterMode = CAN_FILTERMODE_IDLIST;
  CAN_FilterStruct.FilterScale = CAN_FILTERSCALE_16BIT;
  CAN_FilterStruct.FilterActivation = CAN_FILTER_ENABLE;
  HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterStruct);

  CAN_FilterStruct.FilterBank = 1;
  CAN_FilterStruct.FilterFIFOAssignment = CAN_FILTER_FIFO1;
  CAN_FilterStruct.FilterIdHigh = 0x0005;
  CAN_FilterStruct.FilterIdLow = 0x0006;
  CAN_FilterStruct.FilterMaskIdHigh = 0x0007;
  CAN_FilterStruct.FilterMaskIdLow = 0x0008;
  // CAN_FilterStruct.SlaveStartFilterBank = 3;
  CAN_FilterStruct.FilterMode = CAN_FILTERMODE_IDLIST;
  CAN_FilterStruct.FilterScale = CAN_FILTERSCALE_16BIT;
  CAN_FilterStruct.FilterActivation = CAN_FILTER_ENABLE;
  HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterStruct);

  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL);

  HAL_CAN_Start(&hcan1);
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
  if(hcan == &hcan1)
  {
    
  }
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  extern uint8_t RxBuffer[8];
  extern CAN_RxHeaderTypeDef CAN_RxHeaderStruct;
  if(hcan == &hcan1)
  {
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CAN_RxHeaderStruct, RxBuffer);
  }
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#include "slip_exchange.h"

int uart_to_can(slip_decode_t *slip_decode)
{
    HAL_StatusTypeDef ret;
    uint32_t tx_mailbox;
    CAN_TxHeaderTypeDef can_txheader;

    can_txheader.StdId = slip_decode->can_info.node_id;
    can_txheader.ExtId = 0x0;
    can_txheader.IDE = CAN_ID_STD;
    can_txheader.RTR = CAN_RTR_DATA;
    can_txheader.DLC = 8;
    can_txheader.TransmitGlobalTime = DISABLE;

    ret = HAL_CAN_AddTxMessage(&hcan, &can_txheader, slip_decode->can_info.can_array, &tx_mailbox);
    
    return ret==HAL_OK?0:-1;
}

// int can_to_uart()

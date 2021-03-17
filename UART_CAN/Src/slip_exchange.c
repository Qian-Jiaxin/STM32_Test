#include "slip_exchange.h"

int uart_to_can(const slip_can_tx_t *slip_can_tx)
{
    HAL_StatusTypeDef ret;

    CAN_TxHeaderTypeDef can_txheader;
    can_txheader.StdId = *slip_can_tx->node_id;
    can_txheader.ExtId = 0x0;
    can_txheader.IDE = CAN_ID_STD;
    can_txheader.RTR = CAN_RTR_DATA;
    can_txheader.DLC = 8;
    can_txheader.TransmitGlobalTime = DISABLE;

    ret = HAL_CAN_AddTxMessage(&hcan, &can_txheader, slip_can_tx->node_id, *slip_can_tx->tx_mailbox);
    return ret==HAL_OK?0:1;
}
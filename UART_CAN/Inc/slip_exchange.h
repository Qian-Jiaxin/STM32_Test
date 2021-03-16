#ifndef __EXCHANGE_H__
#define __EXCHANGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "can.h"
#include "usart.h"
#include "cmsis_os2.h"


typedef struct 
{
    uint16_t node_id;
    uint32_t *tx_mailbox;
    uint8_t tx_data[8];
}slip_can_tx_t;

typedef struct 
{

}slip_uart_tx_t;







#ifdef __cplusplus
}
#endif

#endif /* __EXCHANGE_H__ */
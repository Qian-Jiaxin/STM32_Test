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
    uint8_t can_array[8];
}can_info_t;

typedef union 
{
    can_info_t can_info;
    uint8_t uart_array[10];
}slip_decode_t;


int uart_to_can(slip_decode_t *slip_decode);


#ifdef __cplusplus
}
#endif

#endif /* __EXCHANGE_H__ */
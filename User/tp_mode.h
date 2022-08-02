#ifndef __TP_MODE_H
#define __TP_MODE_H	 
#include <at32wb415.h>
#include "at_cmd.h"

#define USART_RECV_LEN  			           512

/* mode definition */
#define GET_MDOE_GROUP                   0x00
#define SET_MDOE_GROUP                   0x01

/* type definition */
#define LED_CONTROL_STATUS               0x00

#define tp_data_send                     at_cmd_send
/* payload/control contents*/
typedef enum
{
  TP_LED_OFF                             = 0x00, /*!< led off */
  TP_LED_ON                              = 0x01, /*!< led on */
} led_control_status;

typedef struct{
  uint16_t  buf[USART_RECV_LEN];
  uint16_t  head;
  uint16_t  tail;
  uint16_t  count;
  flag_status recv_end;
} uartstruct;

void tp_mode_rx_handler(void);
void tp_mode_tx_handler(void);
#endif

#include "stdio.h"
#include "string.h"
#include "tp_mode.h"
#include "at32wb415_board.h"

uartstruct tp_mode_rx_uart = {0};
uartstruct tp_mode_tx_uart = {0};

void tp_mode_rx_handler(void)
{
  uint16_t tempval = 0;
  if(tp_mode_rx_uart.count > 0)
  {
    usart_interrupt_enable(USART3, USART_RDBF_INT, FALSE);
    tp_mode_rx_uart.count--;    
    usart_interrupt_enable(USART3, USART_RDBF_INT, TRUE);
    tempval = tp_mode_rx_uart.buf[tp_mode_rx_uart.tail++];
    if(tp_mode_rx_uart.buf[tp_mode_rx_uart.tail-2] == 0x0d  && tp_mode_rx_uart.buf[tp_mode_rx_uart.tail-1] == 0x0a)
    {
      tp_mode_rx_uart.recv_end = SET;
    }

    if(tp_mode_rx_uart.tail > (USART_RECV_LEN - 1))
    {
      tp_mode_rx_uart.tail = 0;
    }      
    while(usart_flag_get(USART2, USART_TDBE_FLAG) !=SET);
    usart_data_transmit(USART2, tempval);
  }
}

void tp_mode_tx_handler(void)
{
  uint16_t tempval = 0;
  if(tp_mode_tx_uart.count > 0)
  {
    usart_interrupt_enable(USART2, USART_RDBF_INT, FALSE);
    tp_mode_tx_uart.count--;    
    usart_interrupt_enable(USART2, USART_RDBF_INT, TRUE);
    tempval = tp_mode_tx_uart.buf[tp_mode_tx_uart.tail++];
    if(tp_mode_tx_uart.buf[tp_mode_tx_uart.tail-2] == 0x0d  && tp_mode_tx_uart.buf[tp_mode_tx_uart.tail-1] == 0x0a)
    {
      tp_mode_tx_uart.recv_end = SET;
    }

    if(tp_mode_tx_uart.tail > (USART_RECV_LEN - 1))
    {
      tp_mode_tx_uart.tail = 0;
    } 
    while(usart_flag_get(USART3, USART_TDBE_FLAG) !=SET);
    usart_data_transmit(USART3, tempval);
  }
}

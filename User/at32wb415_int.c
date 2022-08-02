/**
  **************************************************************************
  * @file     at32wb415_int.c
  * @version  v2.0.2
  * @date     2022-06-28
  * @brief    main interrupt service routines.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "at32wb415_int.h"
#include "string.h"
#include "at_cmd.h"
#include "tp_mode.h"
#define MAX_RX_LENGTH                    (128)

flag_status recv_cmp_flag = RESET;
char recv_data[MAX_RX_LENGTH] = {0};

extern cmd_rsp_status cmd_result;
extern cmd_flash_read_status fr_flag;
extern uint8_t bt_flash_data;
extern uartstruct tp_mode_rx_uart;
extern uartstruct tp_mode_tx_uart;
extern flag_status UART_TP_MODE;
extern flag_status switch_mode_flag;

/** @addtogroup AT32WB415_periph_template
  * @{
  */

/** @addtogroup 415_LED_toggle
  * @{
  */

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* go to infinite loop when hard fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles memory manage exception.
  * @param  none
  * @retval none
  */
void MemManage_Handler(void)
{
  /* go to infinite loop when memory manage exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles bus fault exception.
  * @param  none
  * @retval none
  */
void BusFault_Handler(void)
{
  /* go to infinite loop when bus fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles usage fault exception.
  * @param  none
  * @retval none
  */
void UsageFault_Handler(void)
{
  /* go to infinite loop when usage fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles svcall exception.
  * @param  none
  * @retval none
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  this function handles debug monitor exception.
  * @param  none
  * @retval none
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  this function handles pendsv_handler exception.
  * @param  none
  * @retval none
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
//void SysTick_Handler(void)
//{
//}


void USART2_IRQHandler(void)
{
  uint16_t res;
  if(usart_flag_get(USART2, USART_RDBF_FLAG) != RESET)
  {
    res = usart_data_receive(USART2);
    if(tp_mode_tx_uart.count > (USART_RECV_LEN - 1))
    {
      tp_mode_tx_uart.count = 0;
      tp_mode_tx_uart.head = 0;
      tp_mode_tx_uart.tail = 0;
    }			
    else
    {
      tp_mode_tx_uart.count++;
      tp_mode_tx_uart.buf[tp_mode_tx_uart.head++] = res;
      if(tp_mode_tx_uart.head > (USART_RECV_LEN - 1))
      {
        tp_mode_tx_uart.head = 0;
      }
    }
  }
}

void USART3_IRQHandler(void)
{
  if(UART_TP_MODE && switch_mode_flag == RESET)
  {
    uint16_t res;
    if(usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
    {
      res = usart_data_receive(USART3);
      if(tp_mode_rx_uart.count > (USART_RECV_LEN - 1))
      {
        tp_mode_rx_uart.count = 0;
        tp_mode_rx_uart.head = 0;
        tp_mode_rx_uart.tail = 0;
      }			
      else
      {
        tp_mode_rx_uart.count++;
        tp_mode_rx_uart.buf[tp_mode_rx_uart.head++] = res;
        if(tp_mode_rx_uart.head > (USART_RECV_LEN - 1))
        {
          tp_mode_rx_uart.head = 0;
        }
      }
    }
  }
  else
  {
    static int i = 0;
    uint8_t c;
    
    if(usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
    {
      c = usart_data_receive(USART3);        
      recv_data[i++] = c;
      
      if(c == '\n')
      {
        recv_cmp_flag = SET;
        i = 0;
      }
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */

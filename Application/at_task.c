#include "at_task.h"
#include "at32wb415_board.h"
#include "at_cmd.h"
#include "tp_mode.h"
#include "stdio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

//#define BT_FLASH_WR_TEST
#define SIZEOFMSG   (sizeof(at_cmd_list)/sizeof(struct at_cmd_msg))

extern cmd_flash_read_status fr_flag;
extern cmd_rsp_status cmd_result;
extern flag_status recv_cmp_flag;
extern uint8_t bt_flash_data;
extern char recv_data[];
extern uartstruct tp_mode_rx_uart;
extern uartstruct tp_mode_tx_uart;

flag_status UART_TP_MODE = RESET;
flag_status switch_mode_flag = RESET;

void at_cmd_handler(void);

struct at_cmd_msg at_cmd_list[] =
{
  {AT_CMD_IO_SET_LOW, AT_CMD_IOSET0},
  {AT_CMD_IO_SET_HIGH, AT_CMD_IOSET1},
  {AT_CMD_IO_GET,  AT_CMD_IOGET},
};

button_type BUTTON;
void AT_Task(void *pvParameters)
{
	 printf("AT-Task Start!!\r\n");
	while(1){
	
		if(at32_button_press() == USER_BUTTON)
    {
      UART_TP_MODE = (flag_status)!UART_TP_MODE;
      if(UART_TP_MODE)
      {
        switch_mode_flag = SET;
        at_cmd_send(AT_CMD_TP_MODE_ON);
        while(cmd_rsp_get(AT_TP_MODE_OK1) != RSP_OK);
        switch_mode_flag = RESET;
        at32_led_on(LED3);
        printf("enter uart tp mode\r\n");
      }
      else
      {        
        switch_mode_flag = SET;
        at_cmd_send(AT_CMD_TP_MODE_OFF);
        while(cmd_rsp_get(AT_TP_MODE_OK0) != RSP_OK);
        switch_mode_flag = RESET;
        at32_led_off(LED3);
        printf("leave uart tp mode\r\n");
      }
    }    

    if(UART_TP_MODE)
    {
      tp_mode_rx_handler();
      tp_mode_tx_handler();
    }
    else
    {
      at_cmd_handler();
    }
		
		vTaskDelay(100);
  }
}


/**
  * @brief  handle input at command, it will response corresponding formats.
  * @param  none
  * @retval none
  */
void at_cmd_handler(void)
{
  uint8_t msg_id = SIZEOFMSG-1, i;
  if(recv_cmp_flag == SET)
  { 
      for(i = 0; i <= SIZEOFMSG; i++)
      {
        if(memcmp(recv_data, at_cmd_list[i].at_cmd_string, strlen(recv_data)) == 0)
        {
          printf("%s", recv_data);
          msg_id = i;
          break;
        }
      }
      
      switch(at_cmd_list[msg_id].msg_id)
      {
        case AT_CMD_IOSET0:
        {
          at32_led_off(LED2);
          at_cmd_send(AT_RESULT_OK0);
          break;
        }
        case AT_CMD_IOSET1:
        {
          at32_led_on(LED2);
          at_cmd_send(AT_RESULT_OK1);
          break;
        }
        case AT_CMD_IOGET:
        {
          if(gpio_output_data_bit_read(GPIOB, GPIO_PINS_7))
          {
            at_cmd_send(AT_RESULT_OK1);
          }
          else
          {
            at_cmd_send(AT_RESULT_OK0);
          }
          break;
        }
        default:
        {
          at_cmd_send(AT_RSP_ERROR);
          break;
        }
      }          
    recv_cmp_flag = RESET;
    memset(recv_data, 0, strlen(recv_data));
  }
}


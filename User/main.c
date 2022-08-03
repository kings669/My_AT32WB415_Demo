/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.2
  * @date     2022-06-28
  * @brief    main program
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

#include "at32wb415_board.h"
#include "at32wb415_clock.h"
#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_adc.h"
#include "bsp_usart.h"
#include "usb_task.h"
#include "bsp_pwm.h"
#include "bsp_wdt.h"

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(USART2_IRQn, 0, 1);
	
  system_clock_config();

  at32_board_init();
	at32_button_init();
	
	at32_led_init(LED2);
  at32_led_init(LED3);
	//at32_led_init(LED4);
	led4_pwm_init();
	
	uart_print_init(115200);//usart2
	usart3_init(115200);//usart3
	
	adc1_config();
	dma_config();

	usb_cdc_init();
	
	wdt_init();

	startTask();
	vTaskStartScheduler();
  while(1)
  {
    
  }
}

/**
  * @}
  */

/**
  * @}
  */

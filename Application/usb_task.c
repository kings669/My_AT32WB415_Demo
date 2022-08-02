#include "usb_task.h"
#include "stdio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "at32wb415_board.h"
#include <stdio.h>
#include <stdarg.h>
static uint8_t usb_buf[256];
/* usb global struct define */
otg_core_type otg_core_struct;
uint8_t usb_buffer[256];
void usb_clock48m_select(usb_clk48_s clk_s);


void usb_task(void *pvParameters)
{
	while(1)
	{
		
	}
	
}

void usb_cdc_init(void)
{
	gpio_init_type gpio_init_struct;
  crm_periph_clock_enable(OTG_PIN_GPIO_CLOCK, TRUE);
  gpio_default_para_init(&gpio_init_struct);
	
	  /* enable otgfs clock */
  crm_periph_clock_enable(OTG_CLOCK, TRUE);

  /* select usb 48m clcok source */
  usb_clock48m_select(USB_CLK_HEXT);

  /* enable otgfs irq */
  nvic_irq_enable(OTG_IRQ, 0, 0);

  /* init usb */
  usbd_init(&otg_core_struct,
            USB_FULL_SPEED_CORE_ID,
            USB_ID,
            &cdc_class_handler,
            &cdc_desc_handler);
}

/**
  * @brief  usb 48M clock select
  * @param  clk_s:USB_CLK_HICK, USB_CLK_HEXT
  * @retval none
  */
void usb_clock48m_select(usb_clk48_s clk_s)
{
    switch(system_core_clock)
    {
      /* 48MHz */
      case 48000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1);
        break;

      /* 72MHz */
      case 72000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1_5);
        break;

      /* 96MHz */
      case 96000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2);
        break;

      /* 120MHz */
      case 120000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2_5);
        break;

      /* 144MHz */
      case 144000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3);
        break;

      default:
        break;
    }
}

/**
  * @brief  this function handles otgfs interrupt.
  * @param  none
  * @retval none
  */
void OTG_IRQ_HANDLER(void)
{
  usbd_irq_handler(&otg_core_struct);
}

void usb_delay_ms(uint32_t ms){
	vTaskDelay(ms);
}

//printf redefine 
void usb_printf(const char *fmt,...)
{
    static va_list ap;
    uint16_t len = 0;

    va_start(ap, fmt);

    len = vsprintf((char *)usb_buf, fmt, ap);

    va_end(ap);

		/* send data to host */
    if(usb_vcp_send_data(&otg_core_struct.dev, usb_buf, len) == SUCCESS)
    {
        return;
     }
}
#include "bsp_usart.h"

void usart3_init(uint32_t baudrate)
{
	gpio_init_type gpio_init_struct;
	
	crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);  
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  
  gpio_pin_remap_config(USART3_GMUX_0010, TRUE);
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_7;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_6;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOA, &gpio_init_struct);
	
	nvic_irq_enable(USART3_IRQn, 0, 0);
	
	/* configure uart param */
	usart_init(USART3, baudrate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(USART3, TRUE);
  usart_receiver_enable(USART3, TRUE);
  
  /* Enable the USARTx Interrupt */
  usart_interrupt_enable(USART3, USART_RDBF_INT, TRUE);
  usart_enable(USART3, TRUE); 
}
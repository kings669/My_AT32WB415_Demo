#include "bsp_pwm.h"


void led4_pwm_init(void)
{
  gpio_init_type gpio_init_struct;
	tmr_output_config_type tmr_oc_init_structure;
	uint16_t div_value = 0;
	
	/* tmr4 clock enable */
  crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);

  /* gpioa gpiob clock enable */
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_pins = GPIO_PINS_9;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOB, &gpio_init_struct);
	
	/* compute the div value */
  div_value = (uint16_t)(system_core_clock / 24000000) - 1;

  /* tmr4 time base configuration */
  tmr_base_init(TMR4, 665, div_value);
  tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR4, TMR_CLOCK_DIV1);

  tmr_output_default_para_init(&tmr_oc_init_structure);
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_oc_init_structure.oc_idle_state = FALSE;
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_oc_init_structure.oc_output_state = TRUE;

  tmr_output_channel_config(TMR4, TMR_SELECT_CHANNEL_4, &tmr_oc_init_structure);
  tmr_channel_value_set(TMR4, TMR_SELECT_CHANNEL_4, 83);
  tmr_output_channel_buffer_enable(TMR4, TMR_SELECT_CHANNEL_4, TRUE);

  tmr_period_buffer_enable(TMR4, TRUE);

  /* tmr enable counter */
  tmr_counter_enable(TMR4, TRUE);
}

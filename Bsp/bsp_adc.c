#include "bsp_adc.h"

extern __IO uint16_t adc1_ordinary_value;

void adc1_config(void)
{
  adc_base_config_type adc_base_struct;
  crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
  crm_adc_clock_div_set(CRM_ADC_DIV_6);

  adc_base_default_para_init(&adc_base_struct);
  adc_base_struct.sequence_mode = FALSE;
  adc_base_struct.repeat_mode = TRUE;
  adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
  adc_base_struct.ordinary_channel_length = 1;
  adc_base_config(ADC1, &adc_base_struct);
  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_16, 1, ADC_SAMPLETIME_239_5);
  adc_ordinary_conversion_trigger_set(ADC1, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);
  adc_dma_mode_enable(ADC1, TRUE);
  adc_tempersensor_vintrv_enable(TRUE);

  adc_enable(ADC1, TRUE);
  adc_calibration_init(ADC1);
  while(adc_calibration_init_status_get(ADC1));
  adc_calibration_start(ADC1);
  while(adc_calibration_status_get(ADC1));
}

void dma_config()
{
  dma_init_type dma_init_struct;
  crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
  dma_reset(DMA1_CHANNEL1);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = 1;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)&adc1_ordinary_value;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = FALSE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&(ADC1->odt);
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_HIGH;
  dma_init_struct.loop_mode_enable = TRUE;
  dma_init(DMA1_CHANNEL1, &dma_init_struct);

  dma_channel_enable(DMA1_CHANNEL1, TRUE);
}


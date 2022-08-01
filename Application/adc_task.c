#include "adc_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "at32wb415_board.h"

__IO uint16_t adc1_ordinary_value = 0;

void Adc_Task(void *pvParameters)
{
	printf("internal_temperature_sensor \r\n");
	
	adc_ordinary_software_trigger_enable(ADC1, TRUE);
	while(1){
		
		while(dma_flag_get(DMA1_FDT1_FLAG) == RESET);
    dma_flag_clear(DMA1_FDT1_FLAG);
    printf("internal_temperature = %f deg C\r\n",(ADC_TEMP_BASE - (double)adc1_ordinary_value * ADC_VREF / 4096) / ADC_TEMP_SLOPE + 25);
		
		vTaskDelay(300);
	}
}

#ifndef __ADC_TASK_H_
#define __ADC_TASK_H_
#include "stdio.h"
#include "at32wb415.h"

#define ADC_VREF                         (3.3)
#define ADC_TEMP_BASE                    (1.26)
#define ADC_TEMP_SLOPE                   (-0.00423)


extern void Adc_Task(void *pvParameters);

#endif

#include "led_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "at32wb415_board.h"

void Led2_Task(void *pvParameters)
{
	while(1){
		at32_led_toggle(LED2);
    vTaskDelay(1000);
	}
}

void Led3_Task(void *pvParameters)
{
	while(1){
		at32_led_toggle(LED3);
    vTaskDelay(500);
	}
}

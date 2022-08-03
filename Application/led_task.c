#include "led_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "at32wb415_board.h"
#include "usb_task.h"

void Led2_Task(void *pvParameters)
{
	uint16_t period, pulse, dir;

	period = 665;
  dir = 1;           
  pulse = 0;  
	at32_led_on(LED2);	
	while(1){
		//at32_led_toggle(LED2);
		vTaskDelay(50);
		
//		if(at32_button_press() != USER_BUTTON)
//    {
//			 /* reload wdt counter */
//				wdt_counter_reload();
//		}else{
//			 
//			while(1);
//		}
		
		
    if (dir)
    {
            pulse += 30;      /* ?0???????5000ns */
    }
    else
    {
            pulse -= 30;      /* ??????????5000ns */
    }
				
    if (pulse >= period)
    {
          dir = 0;
    }
        
		if (0 == pulse) 
		{
           
			dir = 1;
       
		}
		tmr_channel_value_set(TMR4, TMR_SELECT_CHANNEL_4, pulse);
       
		
    //vTaskDelay(1000);
	}
}

void Led3_Task(void *pvParameters)
{
	while(1){
		at32_led_toggle(LED3);
    vTaskDelay(500);
	}
}

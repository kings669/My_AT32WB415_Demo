#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"

#include "led_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 1024
static TaskHandle_t StartTask_Handler;

//任务优先级
#define LED2_TASK_PRIO		12
//任务堆栈大小	
#define LED2_STK_SIZE 		128
//任务句柄
TaskHandle_t LED2Task_Handler;


//任务优先级
#define LED3_TASK_PRIO		12
//任务堆栈大小	
#define LED3_STK_SIZE 		128
//任务句柄
TaskHandle_t LED3Task_Handler;

void start_task(void *pvParameters)
{
		taskENTER_CRITICAL();
	  xTaskCreate((TaskFunction_t )Led2_Task,     	
                (const char*    )"Led2_Task",   	
                (uint16_t       )LED2_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED2_TASK_PRIO,	
                (TaskHandle_t*  )&LED2Task_Handler); 
		xTaskCreate((TaskFunction_t )Led3_Task,     	
                (const char*    )"Led3_Task",   	
                (uint16_t       )LED3_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED3_TASK_PRIO,	
                (TaskHandle_t*  )&LED3Task_Handler);						
							
								
    vTaskDelete(StartTask_Handler); //删除开始任务
							
    taskEXIT_CRITICAL();            //退出临界区,任务级临界区不允许嵌套,中断级允许
}

void startTask(void)//在mian函数中调用
{
    xTaskCreate((TaskFunction_t)start_task,          //任务函数
                (const char *)"start_task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄
}


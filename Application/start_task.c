#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"

#include "led_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE 1024
static TaskHandle_t StartTask_Handler;

//�������ȼ�
#define LED2_TASK_PRIO		12
//�����ջ��С	
#define LED2_STK_SIZE 		128
//������
TaskHandle_t LED2Task_Handler;


//�������ȼ�
#define LED3_TASK_PRIO		12
//�����ջ��С	
#define LED3_STK_SIZE 		128
//������
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
							
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
							
    taskEXIT_CRITICAL();            //�˳��ٽ���,�����ٽ���������Ƕ��,�жϼ�����
}

void startTask(void)//��mian�����е���
{
    xTaskCreate((TaskFunction_t)start_task,          //������
                (const char *)"start_task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������
}


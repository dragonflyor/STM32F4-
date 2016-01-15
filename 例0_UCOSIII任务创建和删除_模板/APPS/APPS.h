#ifndef __APPS_H
#define __APPS_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "includes.h"

//UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		128
//������ƿ�
extern OS_TCB StartTaskTCB;
//�����ջ	
extern CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

////�������ȼ�
//#define TASK1_TASK_PRIO		4
////�����ջ��С	
//#define TASK1_STK_SIZE 		128
////������ƿ�
//OS_TCB Task1_TaskTCB;
////�����ջ	
//CPU_STK TASK1_TASK_STK[TASK1_STK_SIZE];
//void task1_task(void *p_arg);

////�������ȼ�
//#define TASK2_TASK_PRIO		5
////�����ջ��С	
//#define TASK2_STK_SIZE 		128
////������ƿ�
//OS_TCB Task2_TaskTCB;
////�����ջ	
//CPU_STK TASK2_TASK_STK[TASK2_STK_SIZE];
////������
//void task2_task(void *p_arg);

////LCDˢ��ʱʹ�õ���ɫ
//int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
//						GRED,  GBLUE, RED,   MAGENTA,       	 
//						GREEN, CYAN,  YELLOW,BROWN, 			
//						BRRED, GRAY };



#endif

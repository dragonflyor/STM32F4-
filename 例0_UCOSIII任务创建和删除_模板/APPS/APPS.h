#ifndef __APPS_H
#define __APPS_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "includes.h"

//UCOSIII中以下优先级用户程序不能使用，ALIENTEK
//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		128
//任务控制块
extern OS_TCB StartTaskTCB;
//任务堆栈	
extern CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

////任务优先级
//#define TASK1_TASK_PRIO		4
////任务堆栈大小	
//#define TASK1_STK_SIZE 		128
////任务控制块
//OS_TCB Task1_TaskTCB;
////任务堆栈	
//CPU_STK TASK1_TASK_STK[TASK1_STK_SIZE];
//void task1_task(void *p_arg);

////任务优先级
//#define TASK2_TASK_PRIO		5
////任务堆栈大小	
//#define TASK2_STK_SIZE 		128
////任务控制块
//OS_TCB Task2_TaskTCB;
////任务堆栈	
//CPU_STK TASK2_TASK_STK[TASK2_STK_SIZE];
////任务函数
//void task2_task(void *p_arg);

////LCD刷屏时使用的颜色
//int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
//						GRED,  GBLUE, RED,   MAGENTA,       	 
//						GREEN, CYAN,  YELLOW,BROWN, 			
//						BRRED, GRAY };



#endif

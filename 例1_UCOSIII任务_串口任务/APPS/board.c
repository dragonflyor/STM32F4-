#include "board.h"


//硬件初始化
void borad_HarwareInit(void)
{
	//OS_ERR err;
	//CPU_SR_ALLOC();
	
	delay_init(168);  //时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
	uart_init(115200);   //串口初始化
	
	INTX_DISABLE();		//关中断,防止滴答定时器对外设初始化的打扰
	LED_Init();         //LED初始化	
	LCD_Init();			//LCD初始化	
	
	POINT_COLOR = RED;
	LCD_ShowString(30,10,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,30,200,16,16,"UCOSIII Examp 6-1");
	LCD_ShowString(30,50,200,16,16,"Task Creat and Del");
	LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,90,200,16,16,"2014/11/25");
	
	//SD卡初始化
	SDCard_Init();
	
	INTX_ENABLE();		//开中断
}

void SDCard_Init(void)
{
	u32 total,free;
//	u8 t=0;	
	u8 res=0;	
	
	W25QXX_Init();				//初始化W25Q128
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"FATFS TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/15");   
	LCD_ShowString(30,130,200,16,16,"Use USMART for test");	   
 	while(SD_Init())//检测不到SD卡
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(30,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
 	exfuns_init();							//为fatfs相关变量申请内存				 
  	f_mount(fs[0],"0:",1); 					//挂载SD卡 
 	res=f_mount(fs[1],"1:",1); 				//挂载FLASH.	
	if(res==0X0D)//FLASH磁盘,FAT文件系统错误,重新格式化FLASH
	{
		LCD_ShowString(30,150,200,16,16,"Flash Disk Formatting...");	//格式化FLASH
		res=f_mkfs("1:",1,4096);//格式化FLASH,1,盘符;1,不需要引导区,8个扇区为1个簇
		if(res==0)
		{
			f_setlabel((const TCHAR *)"1:ALIENTEK");	//设置Flash磁盘的名字为：ALIENTEK
			LCD_ShowString(30,150,200,16,16,"Flash Disk Format Finish");	//格式化完成
		}else LCD_ShowString(30,150,200,16,16,"Flash Disk Format Error ");	//格式化失败
		delay_ms(1000);
	}													    
	LCD_Fill(30,150,240,150+16,WHITE);		//清除显示			  
	while(exf_getfree("0",&total,&free))	//得到SD卡的总容量和剩余容量
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Fatfs Error!");
		delay_ms(200);
		LCD_Fill(30,150,240,150+16,WHITE);	//清除显示			  
		delay_ms(200);
		LED0=!LED0;//DS0闪烁
	}													  			    
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(30,150,200,16,16,"FATFS OK!");	 
	LCD_ShowString(30,170,200,16,16,"SD Total Size:     MB");	 
	LCD_ShowString(30,190,200,16,16,"SD  Free Size:     MB"); 	    
 	LCD_ShowNum(30+8*14,170,total>>10,5,16);				//显示SD卡总容量 MB
 	LCD_ShowNum(30+8*14,190,free>>10,5,16);					//显示SD卡剩余容量 MB		
//	//ADD BY XZ
//	m_creatFile(NULL);	
	//ENDADD
}


//串口接收数据保存在文件中
void m_creatFile(char * pathname)
{
		u8 t=0;	
		mf_open("0:/NCCODE/conndata.txt",FA_OPEN_ALWAYS| FA_READ|FA_WRITE);
	
while(1)
	{
////串口1中断服务程序
////注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
////接收状态
////bit15，	接收完成标志
////bit14，	接收到0x0d
////bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	
		
		//串口收到数据的长度
		int len = USART_RX_STA&0x3fff;
		
		char * conn_recv = (char*)mymalloc(SRAMIN,len+1);
		//void mymemset(void *s,u8 c,u32 count);	//设置内存
		mymemset(conn_recv,0,len+1);	//设置内存
		
		//取串口的数据 
		//void mymemcpy(void *des,void *src,u32 n);//复制内存   
		mymemcpy(conn_recv, USART_RX_BUF,len);
		LCD_ShowString(30,210,200,16,16,(u8*)conn_recv);
		
		if(len>0)
		{
			//发送$$开始的字符串表示文件接收完成
			if(conn_recv[0]=='$'&&conn_recv[1]=='$'){
				//关闭文件
				mf_close();
				
				//释放内存
				//void myfree(u8 memx,void *ptr);  			//内存释放(外部调用)
				myfree(SRAMIN,conn_recv); 
				
				//状态复位
				USART_RX_STA=0;
				
				break;
			}
				//串口接收到的数据保存到本地
				//u8 mf_write(u8*dat,u16 len);
				mf_write((u8*)conn_recv,len);
				//写换行符\n
				mf_write((u8*)"\n",1);
		}
	
		
		//释放内存
		//void myfree(u8 memx,void *ptr);  			//内存释放(外部调用)
		myfree(SRAMIN,conn_recv); 
		
		//状态复位
		USART_RX_STA=0;
		
		t++; 
		//串口轮询时间与等于200ms
		delay_ms(200);		 			   
		LED0=!LED0;
	} 

}


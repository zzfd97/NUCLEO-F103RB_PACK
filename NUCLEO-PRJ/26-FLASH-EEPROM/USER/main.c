#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "lcd.h"
#include "stmflash.h"   
//ALIENTEK Mini STM32开发板范例代码26
//FLASH模拟EEPROM实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 	//数组长度
#define FLASH_SAVE_ADDR  0X08020000 	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
 int main(void)
 { 
	u8 key;
	u16 i = 0, j = 0;
	u8 datatemp[SIZE];
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
//	LCD_Init();			   	//初始化LCD 
 	KEY_Init();				//按键初始化 	
// 	POINT_COLOR=RED;//设置字体为红色 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"FLASH EEPROM TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/12");  
//	LCD_ShowString(60,130,200,16,16,"WK_UP:Write KEY0:Read");
     printf("\r\n >>FLASH EEPROM TEST ..... WK_UP:Write KEY0:Read\r\n");
//	POINT_COLOR=BLUE;
//	//显示提示信息
//	POINT_COLOR=BLUE;//设置字体为蓝色	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)//WK_UP按下,写入STM32 FLASH
		{
//			LCD_Fill(0,150,239,319,WHITE);//清除半屏    
// 			LCD_ShowString(60,150,200,16,16,"Start Write FLASH....");
            printf("Start Write FLASH.......");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
//			LCD_ShowString(60,150,200,16,16,"FLASH Write Finished!");//提示传送完成
            printf("FLASH Write Finished!\r\n");
		}
		if(key==KEY0_PRES)//KEY0按下,读取字符串并显示
		{
// 			LCD_ShowString(60,150,200,16,16,"Start Read FLASH.... ");
            printf("Start Read FLASH.......");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
//			LCD_ShowString(60,150,200,16,16,"The Data Readed Is:  ");//提示传送完成
//			LCD_ShowString(60,170,200,16,16,datatemp);//显示读到的字符串
            printf("The Data Readed Is:  ");
            for(j = 0; j < SIZE; j++)
            {
                printf("%c", datatemp[j]);
            }
            
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}   	   
}












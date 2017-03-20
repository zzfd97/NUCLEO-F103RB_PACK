#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "lcd.h"
#include "stmflash.h"   
//ALIENTEK Mini STM32�����巶������26
//FLASHģ��EEPROMʵ��  
//����֧�֣�www.openedv.com
//�������������ӿƼ����޹�˾ 

//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 	//���鳤��
#define FLASH_SAVE_ADDR  0X08020000 	//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
 int main(void)
 { 
	u8 key;
	u16 i = 0, j = 0;
	u8 datatemp[SIZE];
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
//	LCD_Init();			   	//��ʼ��LCD 
 	KEY_Init();				//������ʼ�� 	
// 	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"FLASH EEPROM TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/12");  
//	LCD_ShowString(60,130,200,16,16,"WK_UP:Write KEY0:Read");
     printf("\r\n >>FLASH EEPROM TEST ..... WK_UP:Write KEY0:Read\r\n");
//	POINT_COLOR=BLUE;
//	//��ʾ��ʾ��Ϣ
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)//WK_UP����,д��STM32 FLASH
		{
//			LCD_Fill(0,150,239,319,WHITE);//�������    
// 			LCD_ShowString(60,150,200,16,16,"Start Write FLASH....");
            printf("Start Write FLASH.......");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
//			LCD_ShowString(60,150,200,16,16,"FLASH Write Finished!");//��ʾ�������
            printf("FLASH Write Finished!\r\n");
		}
		if(key==KEY0_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
// 			LCD_ShowString(60,150,200,16,16,"Start Read FLASH.... ");
            printf("Start Read FLASH.......");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
//			LCD_ShowString(60,150,200,16,16,"The Data Readed Is:  ");//��ʾ�������
//			LCD_ShowString(60,170,200,16,16,datatemp);//��ʾ�������ַ���
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
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}   	   
}











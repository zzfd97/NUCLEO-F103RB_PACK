#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "dma.h"

//ALIENTEK Mini STM32�����巶������18
//DMAʵ��  
//����֧�֣�www.openedv.com
//�������������ӿƼ����޹�˾
   	
const u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA ����ʵ��"};
#define TEXT_LENTH  sizeof(TEXT_TO_SEND)-1			//TEXT_TO_SEND�ַ�������(������������)
u8 SendBuff[(TEXT_LENTH+2)*100];

 int main(void)
 { 
	u16 i;
	u8 t=0; 
	float pro=0;			//���� 
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
//	LCD_Init();			   	//��ʼ��LCD 
	KEY_Init();				//������ʼ��		 	
 	MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)SendBuff,(TEXT_LENTH+2)*100);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,��(TEXT_LENTH+2)*100.
// 	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"DMA TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
// 	LCD_ShowString(60,130,200,16,16,"KEY0:Start");
	//��ʾ��ʾ��Ϣ	   
	for(i=0;i<(TEXT_LENTH+2)*100;i++)//���ASCII�ַ�������
    {
		if(t>=TEXT_LENTH)//���뻻�з�
		{ 
			SendBuff[i++]=0x0d; 
			SendBuff[i]=0x0a; 
			t=0;
		}else SendBuff[i]=TEXT_TO_SEND[t++];//����TEXT_TO_SEND���    
    }		 
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)//KEY0����
		{
			printf("Start Transimit....");
//			LCD_ShowString(60,170,200,16,16,"   %");//��ʾ�ٷֺ�
			printf("\r\nDMA DATA:\r\n "); 	    
		    USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE); //????1?DMA??        
			MYDMA_Enable(DMA1_Channel7);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC7)!=RESET)//�ȴ�ͨ��4�������
				{
					DMA_ClearFlag(DMA1_FLAG_TC7);//���ͨ��4������ɱ�־
					break; 
		        }
				pro=DMA_GetCurrDataCounter(DMA1_Channel7);//�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/((TEXT_LENTH+2)*100);//�õ��ٷֱ�	  
				pro*=100;      //����100��
//				LCD_ShowNum(60,170,pro,3,16);	  
		    }			    
//			LCD_ShowNum(60,170,100,3,16);//��ʾ100%	  
//			LCD_ShowString(60,150,200,16,16,"Transimit Finished!");//��ʾ�������
            printf("Transimit Finished!");//��ʾ�������
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
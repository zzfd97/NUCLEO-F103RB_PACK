#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h" 
//ALIENTEK Mini STM32�����巶������4
//�ⲿ�ж�ʵ��   
//����֧�֣�www.openedv.com
//�������������ӿƼ����޹�˾
 int main(void)
 {	
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
 	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
	LED0=0;				//����LED
	while(1)
	{	    
		printf("OK\n");	
		delay_ms(1000);	  
	} 
}


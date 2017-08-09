#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "key.h"
#include "dac.h"
#include "math.h"
#include "timer.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
 int main(void)
 { 
	u16 adcx;
	float temp;
 	u8 t=0;	 
	float dacval=0;
	u8 key;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	TIM3_Int_Init(19,71);
	delay_init();	    	 //��ʱ������ʼ��	  
//	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
//	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
// 	LCD_Init();			   	//��ʼ��LCD 		
//	KEY_Init();				//������ʼ��		 	
// 	Adc_Init();		  		//ADC��ʼ��
	Dac1_Init();		 	//DACͨ��1��ʼ��	
	    
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);//????0	
	 
	while(1)
	{

//	adcx =	Get_Adc_Average(ADC_Channel_1,10);
	//	printf("%d\r\n",adcx);
	/*	for(dacval=0;dacval<2047;dacval++)
		{
			DAC_SetChannel1Data(DAC_Align_12b_R, (int)(sin((dacval/2047)*6.283185)*2047)+2048);//??DAC?
		//	LCD_ShowxNum(60,200,(int)(sin((dacval/2047)*6.283185)*2047)+2048,4,16,0x08);
			delay_us(2);
		}*/
		/*	for(dacval=4095;dacval>0;dacval--)
		{
			DAC_SetChannel1Data(DAC_Align_12b_R, (int)sin(dacval/4095*1.5708)*4095);//??DAC?
			delay_us(2);
		}*/
	}										    
}	


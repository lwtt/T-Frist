#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "key.h"
#include "dac.h"
#include "math.h"
#include "dma.h"
#include "timer.h"
//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
  u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA ����ʵ��"};
 u16 Send_Buff[80];
	extern  u8 flag;
	
 int main(void)
 { 
	u16 adcx;
	float temp;
 	u16 t=0;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	TIM3_Int_Init(252,71);	 	
	Dac1_Init();		 	//DACͨ��1��ʼ��	
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);//????0	
	Adc_Init_DMA(DMA1_Channel1,(u32)&ADC1->DR);
	ADC_DMACmd(ADC1, ENABLE);	 
	while(1)
	{	
		adcx = Get_DMA_ADc(ADC_Channel_1,200);
		if(adcx<=180&&flag==1)
				TIM_ITConfig(TIM3,TIM_IT_Update ,	ENABLE);  //ʹ���ж�
		
	/*	if(1)
		{
			for(t=0;t<=4000;t++)
			{
				Send_Buff[t]=adcx;
				adcx = Get_DMA_ADc(ADC_Channel_1,200);
			}
			for(t=0;t<=4000;t++)
			{
				printf(" %d",Send_Buff[t]);
			}
			printf("\r\n");
			
		}*/
	//	printf(" %.4f\r\n",((float)adcx/4096)*3.3);
	//	printf(" %d",adcx);
	}										    
}	


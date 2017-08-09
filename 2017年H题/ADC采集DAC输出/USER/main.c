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
//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
  u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA 串口实验"};
 u16 Send_Buff[80];
	extern  u8 flag;
	
 int main(void)
 { 
	u16 adcx;
	float temp,Vr;
 	u16 t=0;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
//	TIM3_Int_Init(252,71);	 	//已失能
	Dac1_Init();		 	//DAC通道1初始化	
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);//设置DAC输出0	
	Adc_Init_DMA(DMA1_Channel1,(u32)&ADC1->DR);
	ADC_DMACmd(ADC1, ENABLE);	 
	while(1)
	{	
		temp=(Get_DMA_ADc(ADC_Channel_2,200)/4096.0)*3.3;
		Vr=AD_DA_Fun(temp);
		adcx=(Vr/3.3)*4096;
		DAC_SetChannel1Data(DAC_Align_12b_R, adcx);
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


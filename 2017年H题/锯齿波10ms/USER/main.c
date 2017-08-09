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

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
 int main(void)
 { 
	u16 adcx;
	float temp;
 	u8 t=0;	 
	float dacval=0;
	u8 key;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	TIM3_Int_Init(19,71);
	delay_init();	    	 //延时函数初始化	  
//	uart_init(9600);	 	//串口初始化为9600
//	LED_Init();		  		//初始化与LED连接的硬件接口
// 	LCD_Init();			   	//初始化LCD 		
//	KEY_Init();				//按键初始化		 	
// 	Adc_Init();		  		//ADC初始化
	Dac1_Init();		 	//DAC通道1初始化	
	    
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


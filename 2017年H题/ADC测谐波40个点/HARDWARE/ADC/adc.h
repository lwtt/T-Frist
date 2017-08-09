#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
							    					    
void Adc_Init_DMA(DMA_Channel_TypeDef* DMA_CHx,u32 cpar);
u32 Get_DMA_ADc(u8 ch , u16 timer); 

 
#endif 

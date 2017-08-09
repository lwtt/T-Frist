 #include "adc.h"
 #include "delay.h"

u32 adcvule[3];				//����32λ�ģ����������
   
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void  Adc_Init_DMA(DMA_Channel_TypeDef* DMA_CHx,u32 cpar)
{
	DMA_InitTypeDef DMA_InitStructure; 
 	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	//PA0/1/2/3 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	


	DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&adcvule;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //������Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = 1;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;  //���ݿ��Ϊ λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; //���ݿ��Ϊ λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���


	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1 
	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ��
	
	ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�	
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
 	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

	
} 
//���ADCֵ
//ch:ͨ��ֵ 0~3
u32 Get_DMA_ADc(u8 ch , u16 timer)   
{
	u32 adcx=0;
	u16 i=0;
  //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����
	while(i < timer)
	{
		adcx = adcx+adcvule[0];
		i++;
	}
	adcx = adcx/timer;
	return adcx;
}





























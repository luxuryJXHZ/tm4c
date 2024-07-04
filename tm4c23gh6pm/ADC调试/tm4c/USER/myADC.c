#include "myADC.h"
void ADC0_D0(void)
{
/*SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
	
ADCSequenceConfigure(ADC0_BASE,0,ADC_TRIGGER_PROCESSOR, 0);
 ADCSequenceStepConfigure (ADC0_BASE,0,0,  ADC_CTL_CH7|ADC_CTL_IE|ADC_CTL_END);
	//ADCSequenceStepConfigure (ADC0_BASE,0,1,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,2,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,3,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,4,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,5,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,6,  ADC_CTL_CH7|ADC_CTL_IE);	
	//ADCSequenceStepConfigure (ADC0_BASE,0,7,  ADC_CTL_CH7|ADC_CTL_IE);
//	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
	ADCSequenceEnable(ADC0_BASE, 0);
	ADCIntClear(ADC0_BASE, 0);
	ADCIntEnable(ADC0_BASE,0);
  
	//IntEnable(INT_ADC1SS0);*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END);
		ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCIntClear(ADC0_BASE, 0);
	ADCIntEnable(ADC0_BASE,0);
 
}
void ADC1_D0(void)
{
/*SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
	
ADCSequenceConfigure(ADC0_BASE,0,ADC_TRIGGER_PROCESSOR, 0);
 ADCSequenceStepConfigure (ADC0_BASE,0,0,  ADC_CTL_CH7|ADC_CTL_IE|ADC_CTL_END);
	//ADCSequenceStepConfigure (ADC0_BASE,0,1,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,2,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,3,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,4,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,5,  ADC_CTL_CH7|ADC_CTL_IE);
	//ADCSequenceStepConfigure (ADC0_BASE,0,6,  ADC_CTL_CH7|ADC_CTL_IE);	
	//ADCSequenceStepConfigure (ADC0_BASE,0,7,  ADC_CTL_CH7|ADC_CTL_IE);
//	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
	ADCSequenceEnable(ADC0_BASE, 0);
	ADCIntClear(ADC0_BASE, 0);
	ADCIntEnable(ADC0_BASE,0);
  
	//IntEnable(INT_ADC1SS0);*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);

    ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, 0, 0, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC1_BASE, 0, 1, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC1_BASE, 0, 2, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC1_BASE, 0, 3, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC1_BASE, 0, 4, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC1_BASE, 0, 5, ADC_CTL_CH8);
		ADCSequenceStepConfigure(ADC1_BASE, 0, 6, ADC_CTL_CH8 );
		ADCSequenceStepConfigure(ADC1_BASE, 0, 7, ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC1_BASE, 0);
		ADCClockConfigSet(ADC1_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
		                             
    ADCIntClear(ADC1_BASE, 0);
	ADCIntEnable(ADC1_BASE,0);
 
}
uint32_t ADC0_D0_Read(uint32_t   *pui32ADC1Value)
{
	int i=0;
	double sum=0;
	ADCProcessorTrigger(ADC0_BASE, 0);
while(!ADCIntStatus(ADC0_BASE, 0, false))
{}
ADCIntClear(ADC0_BASE, 0);

ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC1Value);
for(i=0;i<8;i++){
sum=sum+pui32ADC1Value[i];
}
return sum;
}
uint32_t ADC1_D0_Read(uint32_t   *pui32ADC1Value)
{
	int i=0;
	double sum=0;
	ADCProcessorTrigger(ADC0_BASE, 0);
while(!ADCIntStatus(ADC0_BASE, 0, false))
{}
ADCIntClear(ADC0_BASE, 0);

ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC1Value);
for(i=0;i<8;i++){
sum=sum+pui32ADC1Value[i];
}
return sum;




}
int  My_Printf(uint32_t *m,uint32_t *n,double c,int a,int b)
{
	char t[80];  
	int data;
  int high0;
	int low0;
	double sum;

	int i=0;
  UC1701Clear();
	for(i=0;i<88;i++){
	sum=(double)((m[i]+n[i])/2+sum);
	}
	sum=sum/88;
 data=sum*3300*c/4096;	
	//temp=(double)(data/1000);
	
  low0=data%1000;
  high0=(data-low0)/1000;
	sprintf(t,"%d.%03d",high0,low0);
 
	 UC1701CharDispaly (a,b,t);
	SysCtlDelay(SysCtlClockGet()*0.1);
 return data;



}
void ADC0_DMA_Init(uint32_t   *pui32ADC1Value)
{
	/*SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
 uDMAControlBaseSet(sDMAControlTable);
uDMAChannelAssign( UDMA_CHANNEL_ADC0);
	 uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0, UDMA_ATTR_ALL);
uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_SIZE_32 | UDMA_SRC_INC_NONE |UDMA_DST_INC_32 | UDMA_ARB_8);
	//uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_ATTR_USEBURST);
 uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC0_BASE+ADC_O_SSFIFO0 ),pui32ADC1Value,8);
//uDMAChannelEnable(UDMA_CHANNEL_ADC0);
	uDMAChannelEnable(UDMA_CHANNEL_ADC0);
	//ADCSequenceDMAEnable(ADC0_BASE, 0);
	uDMAEnable();*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    uDMAControlBaseSet(sDMAControlTable);
    uDMAChannelAssign(UDMA_CHANNEL_ADC0);
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0, UDMA_ATTR_ALL);
//uDMAChannelAttributeEnable(UDMA_CH14_ADC0_0, UDMA_ATTR_USEBURST);
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                          UDMA_SIZE_32 | UDMA_SRC_INC_NONE | UDMA_DST_INC_32 | UDMA_ARB_8);
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_MODE_BASIC, (void *)(ADC0_BASE +ADC_O_SSFIFO0),pui32ADC1Value, 20);
    uDMAChannelEnable(UDMA_CHANNEL_ADC0);
		uDMAEnable();
}	
void ADC1_DMA_Init(uint32_t   *pui32ADC1Value)
{
	/*SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
 uDMAControlBaseSet(sDMAControlTable);
uDMAChannelAssign( UDMA_CHANNEL_ADC0);
	 uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0, UDMA_ATTR_ALL);
uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_SIZE_32 | UDMA_SRC_INC_NONE |UDMA_DST_INC_32 | UDMA_ARB_8);
	//uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_ATTR_USEBURST);
 uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC0_BASE+ADC_O_SSFIFO0 ),pui32ADC1Value,8);
//uDMAChannelEnable(UDMA_CHANNEL_ADC0);
	uDMAChannelEnable(UDMA_CHANNEL_ADC0);
	//ADCSequenceDMAEnable(ADC0_BASE, 0);
	uDMAEnable();*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    uDMAControlBaseSet(sDMAControlTable);
    uDMAChannelAssign(UDMA_CH24_ADC1_0);
    uDMAChannelAttributeDisable(UDMA_CHANNEL_SSI1RX, UDMA_ATTR_ALL);
  //uDMAChannelAttributeEnable(UDMA_CH24_ADC1_0, UDMA_ATTR_USEBURST);
    uDMAChannelControlSet(UDMA_CHANNEL_SSI1RX | UDMA_PRI_SELECT,
                          UDMA_SIZE_32 | UDMA_SRC_INC_NONE | UDMA_DST_INC_32 | UDMA_ARB_8);
   // uDMAChannelTransferSet(UDMA_CHANNEL_SSI1RX | UDMA_PRI_SELECT,UDMA_MODE_BASIC, (void *)(ADC1_BASE +ADC_O_SSFIFO0),pui32ADC1Value, 100);
    uDMAChannelEnable(UDMA_CHANNEL_SSI1RX);
		uDMAEnable();
}	
uint32_t ADC0DO_DMARead(uint32_t *pui32ADC1Value)
{ 
	
	int i=0;
	double sum=0;
ADCProcessorTrigger(ADC0_BASE, 0);
	while(!ADCIntStatus(ADC0_BASE, 0, false))
{}
ADCIntClear(ADC0_BASE, 0);
uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC0_BASE+ADC_O_SSFIFO0 ),pui32ADC1Value,8);

	for(i=0;i<8;i++){
sum=sum+pui32ADC1Value[i];
}
return sum;
}
extern uint32_t ADC1_DO_DMARead(uint32_t   *pui32ADC1Value1,uint32_t   *pui32ADC1Value0)
{ 
	
	int cnt=0;
	double sum=0;
	uDMAChannelTransferSet(UDMA_CHANNEL_SSI1RX | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC1_BASE+ADC_O_SSFIFO0 ),pui32ADC1Value1,500);
		uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_MODE_BASIC, (void *)(ADC0_BASE +ADC_O_SSFIFO0),pui32ADC1Value0, 500);
	for(cnt=0;cnt<11;cnt++){
		
ADCProcessorTrigger(ADC1_BASE, 0);
	while(!ADCIntStatus(ADC1_BASE,0,false )){};
		
		ADCIntClear(ADC1_BASE, 0);
		
		ADCProcessorTrigger(ADC0_BASE, 0);
		while(!ADCIntStatus(ADC0_BASE,0,false )){};
	

	ADCIntClear(ADC0_BASE, 0);
}
return sum;
}


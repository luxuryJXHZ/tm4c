#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <start.h>
#include <oled.h>
#include <iic.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "inc/hw_nvic.h"
#include "inc/hw_flash.h"
#include "inc/hw_adc.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_timer.h"

#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"
#include "driverlib/adc.h"
#include "driverlib/cpu.h"
#include "driverlib/uart.h"

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
int adcpe0value[8];
int sum[8];
int i;
char str[20];
void ADC_V();
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);
	ADCSequenceEnable(ADC1_BASE,0);
	UART0_INT();
	UARTEnable(UART0_BASE);
	//配置外设及所需引脚
	InitI2C0();
	ADCSequenceConfigure(ADC1_BASE,0,ADC_TRIGGER_PROCESSOR,0);
	ADCSequenceStepConfigure(ADC1_BASE,0,0,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,1,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,2,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,3,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,4,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,5,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,6,ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC1_BASE,0,7,ADC_CTL_CH0); //配置ADC1，采用ss0序列	
	
//  ADCIntEnable(ADC1_BASE,0);
//	ADCIntRegister(ADC1_BASE,0,ADC_V);
//	IntPrioritySet(INT_ADC1SS0,0);
//	IntEnable(INT_ADC1SS0);
//	IntMasterEnable();
	//设置adc的中断函数
	while(1)
	{	
	  ADCProcessorTrigger(ADC1_BASE,0);
		ADC_V();
		int total=0;
		for(i=0;i<8;i++)
		{total=total+sum[i];
		}
		int average=total/8;
		int zheng=average/1000;
		int xiao=average-zheng*1000;
		sprintf(str,"%d.%d",zheng,xiao);
		}	

}
void ADC_V()
{
//	ADCIntClear(ADC1_BASE,0);
	ADCSequenceDataGet(ADC1_BASE,0,adcpe0value);
	for(i=0;i<8;i++)
	{
		sum[i]=adcpe0value[i]*3300/4096;
	}
	
}
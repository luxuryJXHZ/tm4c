#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>



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
char str1[20];
void ADC_V();
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_5);
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_2);
	ADCSequenceEnable(ADC1_BASE,0);
	//配置外设及所需引脚
	
	ADCSequenceConfigure(ADC1_BASE,0,ADC_TRIGGER_PROCESSOR,0);
	ADCSequenceStepConfigure(ADC1_BASE,0,0,ADC_CTL_CH8);
	ADCSequenceStepConfigure(ADC1_BASE,0,1,ADC_CTL_CH8);
	ADCSequenceStepConfigure(ADC1_BASE,0,2,ADC_CTL_CH8);
	ADCSequenceStepConfigure(ADC1_BASE,0,3,ADC_CTL_CH8);
	ADCSequenceStepConfigure(ADC1_BASE,0,4,ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE,0,5,ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE,0,6,ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE,0,7,ADC_CTL_CH1); //配置ADC1，采用ss0序列	,用AIN0采集高电压，AIN1采集低电压
	
  ADCIntEnable(ADC1_BASE,0);
	ADCIntRegister(ADC1_BASE,0,ADC_V);
	IntPrioritySet(INT_ADC1SS0,0);
	IntEnable(INT_ADC1SS0);
	IntMasterEnable();
	//设置adc的中断函数
	UC1701Init(60000);
	while(1)
	{	
	  ADCProcessorTrigger(ADC1_BASE,0);
		ADC_V();
		int total1=0;
		int total2=0;
		for(i=0;i<4;i++)
		{total1=total1+sum[i];
		}
		for(i=4;i<7;i++)
		{total2=total2+sum[i];
		}
		int average=total1/8;
		int zheng=average/1000;
		int xiao=average-zheng*1000;
		int average1=total2/4.2;
		int zheng1=average1/1000;
		int xiao1=average1-zheng1*1000;
		sprintf(str,"%d.%03d",zheng,xiao);
		sprintf(str1,"%d.%03d",zheng1,xiao1);
		UC1701Clear();
		UC1701CharDispaly(0,0,str);
		UC1701CharDispaly(1,0,str1);
		SysCtlDelay(SysCtlClockGet()/3000*100);
		}
	
}
void ADC_V()
{
	ADCIntClear(ADC1_BASE,0);
	ADCSequenceDataGet(ADC1_BASE,0,adcpe0value);
	for(i=0;i<8;i++)
	{
		sum[i]=adcpe0value[i]*3300/4096;
	}
	
}
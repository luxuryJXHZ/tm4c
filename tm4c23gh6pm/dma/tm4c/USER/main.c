#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <time0.h>

#include "inc/hw_udma.h"
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
#include "inc/hw_pwm.h"
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
#include "driverlib/pwm.h"
#include "driverlib/udma.h"
#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
uint32_t adcpe0value;
int sum;
int i;
int k;
uint8_t udmatable[1024];
#pragma DATA_ALIGN(udmatable, 1024)
char str[20];
void ADC_V();
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	PWM_init();
	PWM_duty( PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, 0.5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	
	uDMAEnable();
	uDMAControlBaseSet(udmatable);
	uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC1,UDMA_ATTR_HIGH_PRIORITY|UDMA_ATTR_ALTSELECT|UDMA_ATTR_REQMASK);
	uDMAChannelControlSet(UDMA_CHANNEL_ADC1| UDMA_PRI_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
	uDMAChannelTransferSet(UDMA_CHANNEL_ADC1|UDMA_PRI_SELECT,UDMA_MODE_PINGPONG,
	(void*)(ADC1_BASE+ADC_O_SSFIFO3),udmatable,1);
	uDMAEnable();
	uDMAChannelRequest(UDMA_CHANNEL_ADC1);
	
	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
	ADC_init_SS3();
	ADCSequenceConfigure(ADC1_BASE,3,ADC_TRIGGER_TIMER,0);
	ADC_SS3_SET(ADC_CTL_CH1);
	TimerLoadSet(TIMER1_BASE,TIMER_B,SysCtlClockGet()*4000-1);
		TimerIntEnable(TIMER1_BASE,TIMER_TIMB_TIMEOUT);
	TimerIntRegister(TIMER1_BASE,TIMER_B,ADC_V);
	TimerEnable (TIMER1_BASE,TIMER_B );
	IntEnable(INT_TIMER1B);
	IntMasterEnable();
	
	UC1701Init(60000);
	while(1)
	{ 	
	  sum=adcpe0value*3300/4096;
		int average=sum;
		int zheng=average/1000;
		int xiao=average-zheng*1000;
		sprintf(str,"%d.%03d",zheng,xiao);
		UC1701Clear();
		UC1701CharDispaly(0,0,str);
		SysCtlDelay(SysCtlClockGet()/3000*100);
	}	
		
		}	
void ADC_V()
{
	TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
 	TimerIntClear(TIMER1_BASE,TIMER_TIMB_TIMEOUT);
	ADCSequenceDataGet(ADC1_BASE,3,&adcpe0value);
	sum=adcpe0value*3300/4096;
 
}
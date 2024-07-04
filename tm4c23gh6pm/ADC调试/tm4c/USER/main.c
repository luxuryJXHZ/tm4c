#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_uart.h>
#include <myADC.h>
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
#include "driverlib/uart.h"a
#include "driverlib/pwm.h"
#include "driverlib/udma.h"
#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
#define ADC_SAMPLE_BUF_SIZE 1024

//dma控制块需要1024字节对齐
static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

int  adcprinmary[8];
uint32_t ADCBuffer1[1024];
uint32_t ADCBuffer2[8];


int main()
{
//	int sum,i=0,cnt=0;
//	SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
//	  ADC0_D0();
//	ADC0_DMA_Init(ADCBuffer1);

//		while(1)
//		{
//			cnt++;
//		ADC0DO_DMARead(ADCBuffer1);
//			for(i=0;i<8;i++)
//			{ADCBuffer2[8*cnt+1]=ADCBuffer1[i];
//			}
//		if(cnt==128)  
//		}
	int sum,i=0,cnt=0;
SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	UART0_INT();
	UARTEnable(UART0_BASE);
 while(1)
 {
	 cnt++;
	 dma_adc_init(PE,P_2,ADC_CTL_CH1,ADCBuffer2);
	 adc_dma_read(ADCBuffer2);
	 for(i=0;i<8;i++)
			{ADCBuffer1[8*cnt+i-8]=ADCBuffer2[i];
				UARTprintf("%d\n",ADCBuffer2[i]);
			}
		if(cnt==128)  cnt=0;
 }
}

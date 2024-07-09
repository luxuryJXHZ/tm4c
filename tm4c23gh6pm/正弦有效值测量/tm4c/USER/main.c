#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <time0.h>
#include <lxy_ADC.h>
#include <math.h>
#include <lxy_uart.h>
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

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"

uint32_t i;
int k,j;
double p;
char str[20];
uint32_t buffer1[8];
uint32_t buffer2[1024];
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	UART0_INT();
	UARTEnable(UART0_BASE);
	UC1701Init(60000);
	while(1)
	{ int max;
		int max1;
		max1=0;
		for(j=0;j<100;j++){
									for(i=0;i<128;i++){
											dma_adc_init(PE,P_2,ADC_CTL_CH1,buffer1);
											adc_dma_read(buffer1);
											for(k=0;k<8;k++)
											{
													buffer2[8*i+k]=buffer1[k]*3300/4096;
											}
									}
									max=0;
										for(i=0;i<1024;i++)
										{
													if(buffer2[i]>max)
													{
														max=buffer2[i];
													}
										}	
										max1=max1+max;
									}
			max1=1.0087*max1/100-11.5833;
   		max1=max1/sqrt(2);
			UARTprintf("%d\n",max1);
			
	}	
		             
		}	

 


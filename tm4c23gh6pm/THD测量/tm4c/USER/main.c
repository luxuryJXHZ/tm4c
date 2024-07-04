#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <time0.h>
#include <lxy_PWM.h>
#include <lxy_ADC.h>
#include <fft.h>
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

#define Num_result                     1024
uint32_t adcpe0value;
uint32_t buffer1[8];
uint32_t buffer2[1024];
float sum[Num_result];
float a[Num_result];
float a2[Num_result];
int i;
int k;
double p;
char str[20];
struct compx a1[Num_result];
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	UART0_INT();
	UARTEnable(UART0_BASE);
	while(1)
	{ 	int i1,i2;
		for(i=0;i<Num_result/8;i++){
			dma_adc_init(PE,P_2,ADC_CTL_CH1,buffer1);
	  	adc_dma_read(buffer1);
			for(k=0;k<8;k++)
			{
			buffer2[8*i+k]=buffer1[k];
			}
	}
		for(i=0;i<Num_result;i++){
			sum[i]=buffer2[i]*3300/4096;

		a1[i].real=sum[i]*1000.0;
		a1[i].imag=0;
		SysCtlDelay(SysCtlClockGet()/3000);
	}

	FFT(a1,Num_result);
	for (i1=1; i1<Num_result; i1++)
                   {
                      a[i1-1] = a1[i1].real*a1[i1].real + a1[i1].imag*a1[i1].imag;
                   }
                 for(i2=1; i2<Num_result; i2++)
                 {
                 a2[i2]=sqrt(a[i2-1]);
									 UARTprintf("%d\n",a2[i2]);
                 }
								 p=get_THD(a2,Num_result);

								 p=p*100;
								 
	}	
		             
		}	

 


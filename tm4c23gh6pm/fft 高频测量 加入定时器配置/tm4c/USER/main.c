#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <time0.h>
#include <lxy_PWM.h>
#include <lxy_ADC.h>
#include <arm_const_structs.h>
#include <fft.h>
#include "arm_math.h"
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
float32_t a1[Num_result*2];
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	ADC_init_SS3();
	ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
	UART0_INT();
	UARTEnable(UART0_BASE);
	while(1)
	{
//		for(i=0;i<Num_result/8;i++){
//			dma_adc_init(PE,P_2,ADC_CTL_CH1,buffer1);
//	  	adc_dma_read(buffer1);
//			for(k=0;k<8;k++)
//			{
//			buffer2[8*i+k]=buffer1[k]*3300/4096;
//			}
//	}
//		for(i=0;i<Num_result;i++){
//		a1[2*i]=buffer2[i];
//		a1[2*i+1]=0;
//	}
//		arm_cfft_f32(&arm_cfft_sR_f32_len1024,a1,0,1);
//	for(i=0;i<Num_result;i++){
//		sum[i]=sqrt(a1[2*i]*a1[2*i]+a1[2*i+1]*a1[2*i+1]);
//	}
//	int max=0;
//	uint32_t fre=0;
//	for(i=1;i<Num_result/2;i++)
//	{
//	if(sum[i]>max)
//	{
//    max=sum[i];
//		fre=i;
//	}
//	}
//	fre=fre*231734/1024;	
//			UARTprintf("%d\n",fre);
//SysCtlDelay(3000000);	
	}	
		             
		}	

 


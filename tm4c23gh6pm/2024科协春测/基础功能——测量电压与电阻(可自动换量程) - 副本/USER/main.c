#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <fft.h>
#include <ADG409BNZ.h>
#include <key.h>


#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"
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
#include "driverlib/pwm.h"

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
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

#define Num_result                     256
uint32_t adcpe0value;
float sum[Num_result];
float a[Num_result];
float a2[Num_result];
int i;
int k;
char str[20];
struct compx a1[Num_result];
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	
	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
	ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
	TimerLoadSet(TIMER1_BASE,TIMER_B,SysCtlClockGet()*4000-1);
	TimerEnable (TIMER1_BASE,TIMER_B );
	
	UC1701Init(60000);
	while(1)
	{ 	int i1,i2;
		double p;
		for(i=0;i<Num_result;i++){
	  	TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
	ADCSequenceDataGet(ADC1_BASE,3,&adcpe0value);
	sum[i]=adcpe0value*3.3/4096;
		a1[i].real=sum[i]*1000.0;
		a1[i].imag=0;
	}
	FFT(a1,Num_result);
	for (i1=1; i1<Num_result; i1++)
                   {
                      a[i1-1] = a1[i1].real*a1[i1].real + a1[i1].imag*a1[i1].imag;
                   }
                 for(i2=1; i2<Num_result; i2++)
                 {
                 a2[i2]=sqrt(a[i2-1]);
                 }
								 p=get_THD(a2,Num_result);
								 p=p*100;
								 int zheng=p/100;
								 int xiao=p-p*100;
								 sprintf(str,"%d.%d",zheng,xiao);
								 UC1701Clear();
								 UC1701CharDispaly(0,0,"THD");
								 UC1701CharDispaly(1,0,str);
								 
	}	
		             
		}	





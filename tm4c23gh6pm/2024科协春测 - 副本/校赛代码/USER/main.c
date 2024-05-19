#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <ADG409BNZ.h>
#include <key.h>
#include <lxy_uart.h>
#include <math.h>


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
void AC_1();
void AC_2();
void AC_3();
void AC_4();
void AC_5();
void qiehuan();
void init();
void gpioinit();
int i=1;
int sum=0;
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	init();
	gpioinit();
	UC1701Init(60000);
	while(1)
	{	
		AC_1();
		SysCtlDelay(SysCtlClockGet()/3000*100);
	}
}

void init()
{	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
}
void gpioinit()
{   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);
		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0);
		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3);
	  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2);
}
void secernprintf(char *str,int x)
{int zheng;
	int xiao;
	zheng=x/1000;
	xiao=x-zheng*1000;
	sprintf(str,"%d.%03d",zheng,xiao);
}
	
void AC_1()
{ 		
//	ADG409BNZ_A0_1;
//	ADG409BNZ_A1_0;
//	ADG409BNZ1_A0_1;
//	ADG409BNZ1_A1_0;
	uint32_t adepeovalue=0; 
			int k;
	int current;
			char str[20];
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			sum =adepeovalue*3300/4096;
//				if(sum >3300)
//				SysCtlPeripheralPowerOff(ADC1_BASE);
//				else
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,sum);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
	}
void AC_2()
{ 		ADG409BNZ_A0_1;
	ADG409BNZ_A1_0;
	ADG409BNZ1_A0_0;
	ADG409BNZ1_A1_0;
	uint32_t adepeovalue=0; 
			int k;
	int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<100;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			if(current>3300)
				SysCtlPeripheralPowerOff(ADC1_BASE);
				else
			sum=sum+current;}
			int average=sum/100;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
	}
void AC_3()
{ 		ADG409BNZ_A0_0;
	ADG409BNZ_A1_0;
	ADG409BNZ1_A0_1;
	ADG409BNZ1_A1_0;
	uint32_t adepeovalue=0; 
			int k;
		int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<100;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
if(current>3300)
				SysCtlPeripheralPowerOff(ADC1_BASE);
				else
			sum=sum+current;}
			int average=sum/100;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
	}
void AC_4()
{ 		ADG409BNZ_A0_0;
	ADG409BNZ_A1_0;
	ADG409BNZ1_A0_0;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
			int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<100;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			if(current>3300)
				SysCtlPeripheralPowerOff(ADC1_BASE);
				else
			sum=sum+current;}
			int average=sum/100;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
	}
void AC_5()
{ 		ADG409BNZ_A0_0;
	ADG409BNZ_A1_0;
	ADG409BNZ1_A0_1;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
	int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<100;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			if(current>3300)
				SysCtlPeripheralPowerOff(ADC1_BASE);
				else
			sum=sum+current;}
			int average=sum/100;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
	}
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
//从1V到10V/0.1V到1V/从1mv到100mv/自动切换量程/过载保护
void AC_1();
void AC_2();
void AC_3();
void AC_4();
int cnt1=0;
//void AC_5();
void up();
void down();
void init();
void gpioinit();
int i=1;
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	init();
	gpioinit();
	key_INT();
	UC1701Init(60000);
	GPIOIntRegister(PD,up);
	GPIOIntRegister(PF,down);
	key_enable();
	while(1)
	{	
		switch(i)
			{case 1:AC_1();break;
				case 2:AC_2();break;
				case 3:AC_3();break;
				case 4:AC_4();break;
				case 5:ADG409BNZ_A0_0;ADG409BNZ_A1_0;break;
		}
		SysCtlDelay(SysCtlClockGet()/3000*500);
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
	  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_7);
}
void secernprintf(char *str,int x)
{int zheng;
	int xiao;
	zheng=x/1000;
	xiao=x-zheng*1000;
	sprintf(str,"%d.%03d",zheng,xiao);
}
	
void up()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTD_BASE,true);
	if((status&GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
{GPIOIntClear(GPIO_PORTD_BASE,status);
i=i+1;}
}
void down()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTF_BASE,true);
	if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
{GPIOIntClear(GPIO_PORTF_BASE,status);
i=i-1;}
}
void AC_1()
{ 		ADG409BNZ_A0_1;
	ADG409BNZ_A1_1;
	ADG409BNZ1_A0_0;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
	int sum;
	int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<2000;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			current=adepeovalue*3300/4096;
				if(current>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
			sum=sum+current;}
			int average=sum/2000;
			average=average*9.976+88;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			if(average>28000)
			{UC1701Clear();
			UC1701CharDispaly(0,0,"error");
			i=5;
			}
			else{
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN1:");
			UC1701CharDispaly(1,0,str);
			UC1701CharDispaly(1,6,"V");}
	}
void AC_2()
{ 		ADG409BNZ_A0_1;
	ADG409BNZ_A1_1;
	ADG409BNZ1_A0_0;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
		int current;
	int sum;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<2000;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			current=adepeovalue*3300/4096;
				if(current>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
			sum=sum+current;}
			int average=sum/2000;
				average=average*10.177-70;	
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN2:");
			UC1701CharDispaly(1,0,str);
				UC1701CharDispaly(1,6,"V");
	}
void AC_3()
{ 		ADG409BNZ_A0_0;
	ADG409BNZ_A1_1;
	ADG409BNZ1_A0_1;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
	int sum;
			int current;
			char str[20];
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<2000;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			current=adepeovalue*3300/4096;
				if(current>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
			sum=sum+current;}
			int average=sum/2000;
			average=average*100+10000;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN3:");
			UC1701CharDispaly(1,0,str);
			UC1701CharDispaly(1,7,"mv");
	}
void AC_4()
{ 		ADG409BNZ_A0_1;
	ADG409BNZ_A1_0;
	ADG409BNZ1_A0_1;
	ADG409BNZ1_A1_1;
	uint32_t adepeovalue=0; 
			int k;
	int current;
			char str[20];
	int sum;
			ADC_init_SS3();
			ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH0);
			TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
			for(k=0;k<100;k++){
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
				current=adepeovalue*3300/4096;
					if(current>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
			sum=sum+current;}
			int average=sum/100;
			average=9.72*average-251;
//			if(sum<0.1)
//			{i=i+1;
//			}
//			if(sum>1)
//			{i=i-1;
//			}
			secernprintf(str,average);
			UC1701Clear();
			UC1701CharDispaly(0,0,"AIN4:");
			UC1701CharDispaly(1,0,str);
			UC1701CharDispaly(1,7,"mv");
	}

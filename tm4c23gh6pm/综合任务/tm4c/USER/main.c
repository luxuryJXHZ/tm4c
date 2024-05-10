#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <start.h>
#include <LED.h>

#include "driverlib/cpu.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "inc/hw_nvic.h"
#include "inc/hw_flash.h"

#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"
#include "uc1701.h"
#include "hw_uc1701.h"
int time_count;
int i;
int a;
char *str;
char str1[100];
void K_1();
void K_2();
void K_3();
void TIMER();
int main(void)
{ 

	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	LED_INT();
	key_INT();
	key_enable();
	TIME_INT();
	UART0_INT();
	GPIOIntRegister(GPIO_PORTD_BASE ,K_1);
	GPIOIntRegister(GPIO_PORTF_BASE ,K_2 );
	GPIOIntRegister(GPIO_PORTA_BASE ,K_3 );
	TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet()/1000-1);
	TimerIntRegister(TIMER0_BASE,TIMER_A,TIMER);
  UC1701Init(60000);
	UC1701Clear();
	while(1)
	{if(a==0)
		{
			LED_RED();
	}
	else	if(a==1)
	{	LED_GREEN(); 
    }
	else
	{	LED_BULE();
	}
}
}
void K_1(void)
{uint32_t V;
	V=GPIOIntStatus(GPIO_PORTD_BASE,true);
	if((V&GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
{GPIOIntClear(GPIO_PORTD_BASE,V);
i=1;}
}
void K_2(void)
{ uint32_t V;
	V=GPIOIntStatus(GPIO_PORTF_BASE,true);
	if((V&GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
{GPIOIntClear(GPIO_PORTF_BASE,V);
i=2;}
}
void K_3(void)
{ 
uint32_t V;
	V=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((V&GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
{GPIOIntClear(GPIO_PORTA_BASE,V);
i=3;}
}

void TIMER()
{TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT );
	time_count++;
	if(i==1)
		{
			if(time_count==500)
	{a=0;
		
	}else if(time_count==1000)
	{a=1;
	}
	else if(time_count==1500)
	{a=2;
		time_count=0;
	}
	}
		else if(i==2)
		{
			if(time_count==1000)
	{a=0;
		
	}else if(time_count==2000)
	{a=1;
	}
	else if(time_count==3000)
	{a=2;
		time_count=0;
	}
	}
		else if(i==3)
		{
			if(time_count==3000)
	{a=0;
		
	}else if(time_count==6000)
	{a=1;
	}
	else if(time_count==9000)
	{a=2;
		time_count=0;
	}
	}
	}
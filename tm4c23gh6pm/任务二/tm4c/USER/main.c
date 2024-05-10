#include "start.h"
#include "LED.h"
#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>

#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_flash.h"

#include "driverlib/cpu.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
void K_1();
void K_2();
void K_3();
void delay_500ms();
void delay_1s();
void delay_3s();
int i;
int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	 LED_INT();
 key_INT();
GPIOIntRegister(GPIO_PORTD_BASE ,K_1);
	GPIOIntRegister(GPIO_PORTF_BASE ,K_2 );
	GPIOIntRegister(GPIO_PORTA_BASE ,K_3 );
 key_enable();
	while(1)
	{	if(i==1)
	{delay_500ms();
	}
else if(i==2)
	{
	delay_1s();
	}
		else if(i==3)
	{
		delay_3s();
	}
}

    }

void delay_500ms()
{
			 LED_RED();
			 SysCtlDelay(SysCtlClockGet()/3000*500);
			 LED_GREEN();
			 SysCtlDelay(SysCtlClockGet()/3000*500);
			 LED_BULE();
			 SysCtlDelay(SysCtlClockGet()/3000*500);

}
void delay_1s()
{
			 LED_RED();
			 SysCtlDelay(SysCtlClockGet()/3000*1000);
			 LED_GREEN();
			 SysCtlDelay(SysCtlClockGet()/3000*1000);
			 LED_BULE();
			 SysCtlDelay(SysCtlClockGet()/3000*1000);
 
}

void delay_3s()
{
  		 LED_RED();
			 SysCtlDelay(SysCtlClockGet()/3000*3000);
			 LED_GREEN();
			 SysCtlDelay(SysCtlClockGet()/3000*3000);
			 LED_BULE();
			 SysCtlDelay(SysCtlClockGet()/3000*3000);
		 
	 
}
void K_1(void)
{uint32_t V;
	V=GPIOIntStatus(GPIO_PORTD_BASE,true);
	if((V&GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
{GPIOIntClear(GPIO_PORTD_BASE,V);
i=1;}
}
void K_2(void)
{uint32_t V;
	V=GPIOIntStatus(GPIO_PORTF_BASE,true);
	if((V&GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
{GPIOIntClear(GPIO_PORTF_BASE,V);
i=2;}
}
void K_3(void)
{uint32_t V;
	V=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((V&GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
{GPIOIntClear(GPIO_PORTA_BASE,V);
i=3;}
}


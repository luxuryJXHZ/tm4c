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
#include "driverlib/timer.h"

void INTHandle_TIMER0A();
int a;
int time_count=0;
int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_4 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	 LED_INT();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC);
	TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet()/1000-1);
	TimerIntRegister(TIMER0_BASE,TIMER_A,INTHandle_TIMER0A);
	IntEnable (INT_TIMER0A );
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
	IntPrioritySet(INT_TIMER0A ,0);
	TimerEnable (TIMER0_BASE,TIMER_A );
	while(1)

	{if(a==0){
			GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
	}
	else	if(a==1)
	{	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
    }
	else 
	{GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0);
	}
		
	}
}
void INTHandle_TIMER0A()
{TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT );
	time_count++;
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


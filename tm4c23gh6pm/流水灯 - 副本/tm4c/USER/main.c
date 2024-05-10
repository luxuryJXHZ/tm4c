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
void after(int ten_us)
{ 
	while(ten_us--);
};
int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;
HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = 0;
	
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_4);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);
	while(1)
	{
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
		SysCtlDelay(SysCtlClockGet()/3000*1000);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
			SysCtlDelay(SysCtlClockGet()/3000*1000);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0);
			SysCtlDelay(SysCtlClockGet()/3000*1000);
    }
	}
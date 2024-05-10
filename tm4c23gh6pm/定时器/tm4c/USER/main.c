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
void LED_INT(void);
void K_1(void);
int main()
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
LED_INT();
		GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_3);
	GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_FALLING_EDGE);
GPIOIntRegister(GPIO_PORTA_BASE ,K_1);
	 GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_3 );
	IntEnable(INT_GPIOD);
	IntMasterEnable();
	while(1)
	{

    }
	}
void LED_INT(void)
{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;
HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = 0;
	
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_4);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
}
void K_1(void)
{uint32_t V;
	V=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((V&GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
{GPIOIntClear(GPIO_PORTA_BASE,V);
     GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
}

}

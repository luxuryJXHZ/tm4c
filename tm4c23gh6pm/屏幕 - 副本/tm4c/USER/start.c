#include "start.h"
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
//**************************************************************************************
//函数名:LED_INT
//功能说明：初始化三个LED
//形参：无
//返回值：无
//**************************************************************************************
void LED_INT()
{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;
HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = 0;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
HWREG(GPIO_PORTD_BASE + GPIO_O_CR)  |= GPIO_PIN_7;
HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x00;
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_4);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
}
//**************************************************************************************
//函数名:key_INT
//功能说明：初始化三个按键，并进行使能
//形参：无
//返回值：无
//**************************************************************************************
void key_INT()
{	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_7);
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
		GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_3);
		GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_2);
	
	GPIOIntTypeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
	GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_FALLING_EDGE);
}
//**************************************************************************************
//函数名:key_INT
//功能说明：使能三个按键
//形参：无
//返回值：无
//**************************************************************************************
void key_enable()
{	 GPIOIntEnable(GPIO_PORTD_BASE,GPIO_PIN_7 );
	IntEnable(INT_GPIOD);
	IntMasterEnable();
	
		 GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_4 );
	IntEnable(INT_GPIOF);
	IntMasterEnable();

	
		 GPIOIntEnable(GPIO_PORTA_BASE,GPIO_INT_PIN_3 );
	IntEnable(INT_GPIOA);
	IntMasterEnable();
}
//**************************************************************************************
//函数名:TIME_INT
//功能说明：使能三个按键
//形参：无
//返回值：无
//**************************************************************************************
void TIME_INT()
{	IntPrioritySet(INT_TIMER0A ,0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC);	
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
	TimerEnable (TIMER0_BASE,TIMER_A );
}
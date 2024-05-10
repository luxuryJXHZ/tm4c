#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>

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
void uart_handle(void);
int main(void)
{ 

	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA );
	SysCtlPeripheralEnable (SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0);
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_1);
	UARTStdioConfig(0,115200,SysCtlClockGet());
	UARTIntEnable( UART0_BASE,  UART_INT_RX|UART_INT_RT);
	UARTIntRegister( UART0_BASE, uart_handle);
	IntPrioritySet( INT_UART0, 0);
	IntEnable( INT_UART0);
	IntMasterEnable();
	UARTEnable(UART0_BASE);

	while(1){
		
	}
}
void uart_handle()
{uint32_t ststus;
	char a;
	ststus=UARTIntStatus (UART0_BASE,true);
	UARTIntClear (UART0_BASE,ststus);
	a=UARTCharGet(UART0_BASE);
	UARTprintf ("%c",a);
	
}
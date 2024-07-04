#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <start.h>
#include <lxy_uart.h>


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

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"


//**************************************************************************************
//函数名:UART0_INIT
//功能说明：有关UART0的初始化
//形参：无
//返回值：无
//**************************************************************************************
void UART0_INT()
{SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA );
	SysCtlPeripheralEnable (SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0);
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_1);
	UARTStdioConfig(0,115200,SysCtlClockGet());
}
//**************************************************************************************
//函数名:UART0_enable
//功能说明：注册有关UART0的函数
//形参：无
//返回值：无
//**************************************************************************************
void UART0_enable()
{UARTIntEnable( UART0_BASE,  UART_INT_RX|UART_INT_RT);
	IntPrioritySet( INT_UART0, 0);
	IntEnable( INT_UART0);
	IntMasterEnable();
	UARTEnable(UART0_BASE);

}

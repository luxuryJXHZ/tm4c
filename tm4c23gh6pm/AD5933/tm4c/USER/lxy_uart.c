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
//������:UART0_INIT
//����˵�����й�UART0�ĳ�ʼ��
//�βΣ���
//����ֵ����
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
//������:UART0_enable
//����˵����ע���й�UART0�ĺ���
//�βΣ���
//����ֵ����
//**************************************************************************************
void UART0_enable()
{UARTIntEnable( UART0_BASE,  UART_INT_RX|UART_INT_RT);
	IntPrioritySet( INT_UART0, 0);
	IntEnable( INT_UART0);
	IntMasterEnable();
	UARTEnable(UART0_BASE);

}

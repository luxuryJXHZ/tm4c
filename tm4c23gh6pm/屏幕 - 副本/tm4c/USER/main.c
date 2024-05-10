#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
void uart_handle(void);
char str[100];
int main(void)
{ SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	int a=100;
	char str[100];
	
	UC1701Init(60000);
	while(a>0)
	{ SysCtlDelay(SysCtlClockGet()/3000*1000);
		a--;
		sprintf(str,"%d",a);
		UC1701Clear();
		UC1701CharDispaly(0,0,str);
	}
	
	while(1){
		
	}
}



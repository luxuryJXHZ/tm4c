#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <key.h>
#include <LED.h>


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
void up1();
void down1();
void go();
int i=0;
struct{
	int current;
	int up;
	int down;
	int enter;
} key_table[9]=
{
	{0,0,0,1,},
	
	{1,2,2,3},
	{2,1,1,6},
	
	{3,5,4,3},
	{4,3,5,4},
	{5,4,3,5},
	
	{6,8,7,6},
	{7,6,8,7},
	{8,7,6,8},
	
};
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	key_INT();
	GPIOIntRegister(PD,up1);
	GPIOIntRegister(PF,down1);
	GPIOIntRegister(PA,go);
	
	key_enable();
	
	UC1701Init(60000);
	
	while(1)
	{	
    switch (i)
			{case 0:UC1701Clear();UC1701CharDispaly(0,0,"start");break;
				case 1:UC1701Clear();UC1701CharDispaly(0,0,"1<");UC1701CharDispaly(1,0,"2");break;
				case 2:UC1701Clear();UC1701CharDispaly(0,0,"1");UC1701CharDispaly(1,0,"2<");break;
				case 3:UC1701Clear();UC1701CharDispaly(0,0,"A<");UC1701CharDispaly(1,0,"B");UC1701CharDispaly (2,0,"C");break;
				case 4:UC1701Clear();UC1701CharDispaly(0,0,"A");UC1701CharDispaly(1,0,"B<");UC1701CharDispaly (2,0,"C");break;
				case 5:UC1701Clear();UC1701CharDispaly(0,0,"A");UC1701CharDispaly(1,0,"B");UC1701CharDispaly (2,0,"C<");break;
				case 6:UC1701Clear();UC1701CharDispaly(0,0,"a<");UC1701CharDispaly(1,0,"b");UC1701CharDispaly (2,0,"c");break;
				case 7:UC1701Clear();UC1701CharDispaly(0,0,"a");UC1701CharDispaly(1,0,"b<");UC1701CharDispaly (2,0,"c");break;
				case 8:UC1701Clear();UC1701CharDispaly(0,0,"a");UC1701CharDispaly(1,0,"b");UC1701CharDispaly (2,0,"c<");break;
				SysCtlDelay(SysCtlClockGet()/3000*1000);
		}
	}
}
void up1()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTD_BASE,true);
	if((status&GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
{GPIOIntClear(GPIO_PORTD_BASE,status);
i=key_table[i].up;}
}
void down1()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTF_BASE,true);
	if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
{GPIOIntClear(GPIO_PORTF_BASE,status);
i=key_table[i].down;}
}
void go()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((status&GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
{GPIOIntClear(GPIO_PORTA_BASE,status);
i=key_table[i].enter;}}





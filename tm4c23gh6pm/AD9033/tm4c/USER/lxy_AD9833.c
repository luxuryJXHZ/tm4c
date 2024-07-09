#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_AD9833.h>


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

void GPIO_INIT()
{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0);
		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3);
	NSS1;
	CLK1;
	data1;
}
void delay(int t)
{SysCtlDelay(SysCtlClockGet()/3000*t);
}
//***********************************
//函数名:dac_sendbite
//功能：用SPI发送一个16位的数据
//参数：发送的数据
//返回值：无
//********************************************
void dac_sendbite(uint16_t a)
{ int i;
	
	NSS0;
	SysCtlDelay(10);
	for ( i=0;i<16;i++)
	{CLK1;
		
		if(0x8000&a) 
		{data1;
		}
	else 
	{data0;
	}
	SysCtlDelay(10);
	CLK0;
	a=a<<1;
	SysCtlDelay(10);
	
	}
	NSS1;
	CLK1;
	data1;
	
}
void AD_register(int value)
{
    NSS0;
    dac_sendbite(value);
    NSS1;	
}
int AD_Init(void)
{
  GPIO_INIT();
	AD_register(AD9833_REG_CMD|AD9833_RESET);
	
	return 1;
}

void AD_reset(void)
{
 AD_register(AD9833_REG_CMD | AD9833_RESET);
}

void AD_clear(void)
{
  AD_register(AD9833_REG_CMD);
}

void AD_frequebcy(unsigned short reg,  unsigned short wave_type,  unsigned long val)
{
    unsigned short  freqHi = reg;
	unsigned short  freqLo = reg;
	
	freqHi |= (val & 0xFFFC000) >> 14 ;
	freqLo |= (val & 0x3FFF);

	AD_register(AD9833_B28);
	AD_register(freqLo);
	AD_register(freqHi);
	AD_register(AD9833_REG_CMD | AD9833_B28 | wave_type);
}

void AD_phase(unsigned short reg, unsigned short val)
{
unsigned short phase = reg;
	phase |= val;
	AD_register(phase);

}

void AD9833_Setup(unsigned short freq,
				  unsigned short phase,
			 	  unsigned short type)
{
	unsigned short val = 0;
	
	val = freq | phase | type;
	AD_register(val);
}

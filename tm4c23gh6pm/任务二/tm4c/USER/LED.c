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
#include "LED.h"
#include "start.h"
//**************************************************************************************
//函数名:LED_RED
//功能说明：点亮红灯
//形参：无
//返回值：无
//**************************************************************************************
void LED_RED()
{ key_INT ();
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
	
}
//**************************************************************************************
//函数名:LED_GREEN
//功能说明：点亮蓝灯
//形参：无
//返回值：无
//**************************************************************************************
void LED_GREEN()
{	key_INT(); 	
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
		GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
}
//**************************************************************************************
//函数名:LED_BULE
//功能说明：点亮蓝灯
//形参：无
//返回值：无
//**************************************************************************************
void LED_BULE()
{key_INT ();
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0);
		
}
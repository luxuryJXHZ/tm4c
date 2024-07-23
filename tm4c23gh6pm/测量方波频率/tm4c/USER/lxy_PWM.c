#include <lxy_PWM.h>
#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
#include "inc/hw_pwm.h"

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
#include "driverlib/pwm.h"
//**************************************************************************************
//函数名:PWM_init
//功能说明：初始化pwm
//形参：无
//返回值：无
//**************************************************************************************
void PWM_init()
{	
		SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
		
		GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2);
		GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_3);
		GPIOPinConfigure(GPIO_PF2_M1PWM6);
		GPIOPinConfigure(GPIO_PF3_M1PWM7);
		
		PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_UP_DOWN);
		PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,5000);
		PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,PWMGenPeriodGet(PWM1_BASE,PWM_GEN_3)*0.1-1);
		PWMPulseWidthSet(PWM1_BASE,PWM_OUT_7,PWMGenPeriodGet(PWM1_BASE,PWM_GEN_3)*0.1-1);
		PWMOutputState(PWM1_BASE,PWM_OUT_6_BIT,true);
		PWMOutputState(PWM1_BASE,PWM_OUT_7_BIT,true);
		PWMGenEnable(PWM1_BASE,PWM_GEN_3);
}
//**************************************************************************************
//函数名:PWM_duty
//功能说明：设置pwm的占空比
//形参：pwm的地址，pwm输出口，pwm的地址位，pwm的基带，以及占空比
//返回值：无
//**************************************************************************************
void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty)
{
    PWMPulseWidthSet( ui32Base,  ui32PWMOut,
                              PWMGenPeriodGet(ui32Base, ui32Gen)*duty - 1);
	PWMOutputState( ui32Base,  ui32PWMOutBits,
                            true);
	PWMGenEnable( ui32Base,  ui32Gen);
}
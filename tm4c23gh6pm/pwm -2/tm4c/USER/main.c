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
void PWM_init();
void LED_Config(void);
void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty);
int main(void)
	{
		PWM_init();
float duty1=0.25;
float duty=0.55;	
	while(1)
	{	
		    PWM_duty( PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, duty1);
		    PWM_duty( PWM1_BASE, PWM_OUT_7, PWM_OUT_7_BIT, PWM_GEN_3, duty);
		
	}
}
void PWM_init()
{	SysCtlClockSet(SYSCTL_SYSDIV_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
		
		GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2);
		GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_3);
		GPIOPinConfigure(GPIO_PF2_M1PWM6);
		GPIOPinConfigure(GPIO_PF3_M1PWM7);
		
		PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_UP_DOWN);
		PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,2000);
		PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,PWMGenPeriodGet(PWM1_BASE,PWM_GEN_3)*0.1-1);
		PWMPulseWidthSet(PWM1_BASE,PWM_OUT_7,PWMGenPeriodGet(PWM1_BASE,PWM_GEN_3)*0.1-1);
		PWMOutputState(PWM1_BASE,PWM_OUT_6_BIT,true);
		PWMOutputState(PWM1_BASE,PWM_OUT_7_BIT,true);
		PWMGenEnable(PWM1_BASE,PWM_GEN_3);
}
void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty)
{
    PWMPulseWidthSet( ui32Base,  ui32PWMOut,
                              PWMGenPeriodGet(ui32Base, ui32Gen)*duty - 1);
	PWMOutputState( ui32Base,  ui32PWMOutBits,
                            true);
	PWMGenEnable( ui32Base,  ui32Gen);
}
	

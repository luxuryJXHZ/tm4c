#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <time0.h>
#include <lxy_PWM.h>

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

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
void jishu();
void jiange();
int cnt=0;
int sum=0;
int cnt1=0;
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//	PWM_init();
//	PWM_duty( PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, 0.5);
	TIME_INT();
	TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet()/30000);
	TimerIntRegister (TIMER0_BASE,TIMER_A,jishu);//开启定时器中断
	GPIOPinTypeGPIOInput(PA,P_2);
	GPIOIntTypeSet(PA,P_2,GPIO_BOTH_EDGES);

	GPIOIntRegister(PA,jiange);
	GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_2);
	IntEnable(INT_GPIOA);
	IntMasterEnable();
	UC1701Init (60000);
	
	while(1)
	{	char str[20];
		char str1[20];
		int f;
		int g;
			f=sum/2;
		g=cnt1/3;
		int zheng=g/100;
		int xiao=g-zheng*100;
		sprintf(str,"%d",f);
		sprintf(str1,"%d.%02d%c",zheng,xiao,'%');
		UC1701Clear();
		UC1701CharDispaly(0,0,"frequence");
		UC1701CharDispaly(1,0,str);
		UC1701CharDispaly(2,0,"duty");
		UC1701CharDispaly(3,0,str1);
		
	}
}
void jiange(){
uint32_t status;
	status=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((status&GPIO_INT_PIN_2)==GPIO_INT_PIN_2)
{GPIOIntClear(GPIO_PORTA_BASE,status);
	if(cnt<30000)
sum++;}
}
void jishu()
{TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT );
	if(cnt<30000)
	{cnt++;}
	if(sum%2==0&&cnt<30000) cnt1++;
}
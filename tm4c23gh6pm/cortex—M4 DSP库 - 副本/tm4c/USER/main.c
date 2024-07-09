#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <time0.h>
#include <lxy_uart.h>
#include <lxy_ADC.h>
#include <fft.h>
#include <math.h>
#include "arm_math.h"
#include "dsp/transform_functions.h"
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

#define Num_result                     1024
#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "debug.h"
#include "fpu.h"
#include "gpio.h"
#include "pin_map.h"
#include "rom.h"
#include "sysctl.h"
#include "uart.h"
#include "uartstdio.h"
#include "arm_math.h" 

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************



#define	DELTA	0.000001f		//误差值
 uint8_t timeout;//定时器溢出次数
//sin cos测试
//angle:起始角度
//times:运算次数
//mode:0,不使用DSP库;1,使用DSP库
//返回值：0,成功;0XFF,出错
uint8_t sin_cos_test(float angle,uint32_t times,uint8_t mode)
{
	float sinx,cosx;
	float result;
	uint32_t i=0;
	if(mode==0)
	{
		for(i=0;i<times;i++)
		{
			arm_cfft_f32();
			cosx=cosf(angle);			//不使用DSP优化的sin，cos函数
			sinx=sinf(angle);
			result=sinx*sinx+cosx*cosx; //计算结果应该等于1  
			result=fabsf(result-1.0f);	//对比与1的差值
			if(result>DELTA)return 0XFF;//判断失败 
			angle+=0.001f;				//角度自增
		}
	}else
	{
		for(i=0;i<times;i++)
		{
			cosx=arm_cos_f32(angle);	//使用DSP优化的sin，cos函数
			sinx=arm_sin_f32(angle);
			result=sinx*sinx+cosx*cosx; //计算结果应该等于1  
			result=fabsf(result-1.0f);	//对比与1的差值
			if(result>DELTA)return 0XFF;//判断失败 
			angle+=0.001f;				//角度自增
		}
	}
	return 0;//任务完成
} 
void Timer0IntHandler(void)
{
  ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	timeout++;
}

void Timer0Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	
	// Configure the two 32-bit periodic timers.
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000);
	
	TimerIntRegister(TIMER0_BASE,TIMER_A, Timer0IntHandler);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	
	TimerEnable(TIMER0_BASE, TIMER_A);
	
	
	ROM_IntMasterEnable();
}



int main(void)
{
	uint8_t i=0;
	int time; 
	uint8_t res;
	
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);		//使用PLL，2.5分频，为80MHz
	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();//打开浮点运算，但是会消耗额外的堆栈空间	
	UART0_INT();
	UARTEnable(UART0_BASE);
	Timer0Init();

	while(1)
	{
		//不使用DSP优化
		TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000);//重设TIM3定时器的计数器值
		timeout=0;
		res=sin_cos_test(PI/6,200000,0);
		time=(int)TimerValueGet(TIMER0_BASE,TIMER_A)/80000+(int)timeout*1000;
		UARTprintf("DSP:%d  ",time);
		UARTprintf("timeout:%d\r\n",timeout);
		//使用DSP优化		
		TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000);//重设TIM3定时器的计数器值
		timeout=0;
		res=sin_cos_test(PI/6,200000,1);
		time=(int)TimerValueGet(TIMER0_BASE,TIMER_A)/80000+(int)timeout*1000;
		UARTprintf("NoDSP:%d  ",time);
		UARTprintf("timeout:%d\r\n",timeout);
		
	}
}


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



#define	DELTA	0.000001f		//���ֵ
 uint8_t timeout;//��ʱ���������
//sin cos����
//angle:��ʼ�Ƕ�
//times:�������
//mode:0,��ʹ��DSP��;1,ʹ��DSP��
//����ֵ��0,�ɹ�;0XFF,����
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
			cosx=cosf(angle);			//��ʹ��DSP�Ż���sin��cos����
			sinx=sinf(angle);
			result=sinx*sinx+cosx*cosx; //������Ӧ�õ���1  
			result=fabsf(result-1.0f);	//�Ա���1�Ĳ�ֵ
			if(result>DELTA)return 0XFF;//�ж�ʧ�� 
			angle+=0.001f;				//�Ƕ�����
		}
	}else
	{
		for(i=0;i<times;i++)
		{
			cosx=arm_cos_f32(angle);	//ʹ��DSP�Ż���sin��cos����
			sinx=arm_sin_f32(angle);
			result=sinx*sinx+cosx*cosx; //������Ӧ�õ���1  
			result=fabsf(result-1.0f);	//�Ա���1�Ĳ�ֵ
			if(result>DELTA)return 0XFF;//�ж�ʧ�� 
			angle+=0.001f;				//�Ƕ�����
		}
	}
	return 0;//�������
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
	
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);		//ʹ��PLL��2.5��Ƶ��Ϊ80MHz
	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();//�򿪸������㣬���ǻ����Ķ���Ķ�ջ�ռ�	
	UART0_INT();
	UARTEnable(UART0_BASE);
	Timer0Init();

	while(1)
	{
		//��ʹ��DSP�Ż�
		TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000);//����TIM3��ʱ���ļ�����ֵ
		timeout=0;
		res=sin_cos_test(PI/6,200000,0);
		time=(int)TimerValueGet(TIMER0_BASE,TIMER_A)/80000+(int)timeout*1000;
		UARTprintf("DSP:%d  ",time);
		UARTprintf("timeout:%d\r\n",timeout);
		//ʹ��DSP�Ż�		
		TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000);//����TIM3��ʱ���ļ�����ֵ
		timeout=0;
		res=sin_cos_test(PI/6,200000,1);
		time=(int)TimerValueGet(TIMER0_BASE,TIMER_A)/80000+(int)timeout*1000;
		UARTprintf("NoDSP:%d  ",time);
		UARTprintf("timeout:%d\r\n",timeout);
		
	}
}


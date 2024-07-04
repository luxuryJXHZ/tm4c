#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>


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
//**************************************************************************************
//函数名:ADC_init_SS0
//功能说明：初始化ADC模块设置序列为SS0
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_init_SS0(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,0);
}
//**************************************************************************************
//函数名:ADC_init_SS1
//功能说明：初始化ADC模块，设置序列为SS1
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_init_SS1(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,1);
}
//**************************************************************************************
//函数名:ADC_init_SS2
//功能说明：初始化ADC模块，设置序列为SS2
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_init_SS2(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,2);
}
//**************************************************************************************
//函数名:ADC_init_SS3
//功能说明：初始化ADC模块
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_init_SS3(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,3);
}
//**************************************************************************************
//函数名:ADC_SS0_SET
//功能说明：设置采集模式为SS0
//形参：uint32_t ui32Config（串口号）
//返回值：无
//**************************************************************************************	
void ADC_SS0_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,0,0,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,1,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,2,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,3,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,4,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,5,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,6,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,0,7,ui32Config);
}
//*************************************************************************************//**************************************************************************************
//函数名:ADC_SS1_SET
//功能说明：设置采集模式为SS1
//形参：uint32_t ui32Config（串口号）
//返回值：无
//**************************************************************************************	
void ADC_SS1_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,1,0,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,1,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,2,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,3,ui32Config);

}
//**************************************************************************************
//函数名:ADC_SS2_SET
//功能说明：设置采集模式为SS2
//形参：uint32_t ui32Config（串口号）
//返回值：无
//**************************************************************************************	
void ADC_SS2_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,2,0,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,1,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,2,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,3,ui32Config);

}
//**************************************************************************************
//函数名:ADC_SS3_SET
//功能说明：设置采集模式为SS3
//形参：uint32_t ui32Config（串口号）
//返回值：无
//**************************************************************************************	
void ADC_SS3_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,3,0,ui32Config|ADC_CTL_END);

}
//**************************************************************************************
//函数名:ADC_SS0_INT
//功能说明：设置ADC在SS0下的中断
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_SS0_INT()
{ADCIntEnable(ADC1_BASE,0);
	IntPrioritySet(INT_ADC1SS0,0);
	IntEnable(INT_ADC1SS0);
	IntMasterEnable();
}
//**************************************************************************************
//函数名:ADC_SS1_INT
//功能说明：设置ADC在SS1下的中断
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_SS1_INT()
{ADCIntEnable(ADC1_BASE,1);
	IntPrioritySet(INT_ADC1SS1,0);
	IntEnable(INT_ADC1SS1);
	IntMasterEnable();
}
//**************************************************************************************
//函数名:ADC_SS2_INT
//功能说明：设置ADC在SS2下的中断
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_SS2_INT()
{ADCIntEnable(ADC1_BASE,2);
	IntPrioritySet(INT_ADC1SS2,0);
	IntEnable(INT_ADC1SS2);
	IntMasterEnable();
}
//**************************************************************************************
//函数名:ADC_SS3_INT
//功能说明：设置ADC在SS3下的中断
//形参：无
//返回值：无
//**************************************************************************************	
void ADC_SS3_INT()
{ADCIntEnable(ADC1_BASE,3);
	IntPrioritySet(INT_ADC1SS3,0);
	IntEnable(INT_ADC1SS3);
	IntMasterEnable();
}


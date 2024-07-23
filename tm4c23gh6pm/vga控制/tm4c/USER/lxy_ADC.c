#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_udma.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/udma.h"

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
void ADC_SS0_SET(uint32_t ui32Trigger,uint32_t ui32Config)
{	
	ADCSequenceConfigure (ADC1_BASE, 0, ui32Trigger, 0);
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
void ADC_SS1_SET(uint32_t ui32Trigger,uint32_t ui32Config)
{	 
	ADCSequenceConfigure(ADC1_BASE, 0,ui32Trigger, 1);
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
void ADC_SS2_SET(uint32_t ui32Trigger,uint32_t ui32Config)
{	
	ADCSequenceConfigure(ADC1_BASE, 0, ui32Trigger, 2);
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
void ADC_SS3_SET(uint32_t ui32Trigger,uint32_t ui32Config)
{	ADCSequenceConfigure(ADC1_BASE, 0, ui32Trigger, 3);
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

void secernprintf(char *str,int x)
{int zheng;
	int xiao;
	zheng=x/1000;
	xiao=x-zheng*1000;
	sprintf(str,"%d.%03d",zheng,xiao);
}

void dma_adc_init(uint32_t ui32Port, uint8_t ui8Pins,uint32_t ui32Config,uint32_t *buffer)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	GPIOPinTypeADC(ui32Port, ui8Pins);
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ui32Config);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ui32Config);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ui32Config );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ui32Config);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ui32Config);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ui32Config );
		ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ui32Config );
	ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ui32Config | ADC_CTL_IE | ADC_CTL_END);
		ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);

    ADCIntClear(ADC0_BASE, 0);
	ADCIntEnable(ADC0_BASE,0);
	

    uDMAControlBaseSet(ControlTable);
    uDMAChannelAssign(UDMA_CHANNEL_ADC0);
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0, UDMA_ATTR_ALL);
//uDMAChannelAttributeEnable(UDMA_CH14_ADC0_0, UDMA_ATTR_USEBURST);
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                          UDMA_SIZE_32 | UDMA_SRC_INC_NONE | UDMA_DST_INC_32 | UDMA_ARB_8);
    uDMAChannelEnable(UDMA_CHANNEL_ADC0);
		uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC0_BASE+ADC_O_SSFIFO0 ),buffer,8);
		uDMAEnable();
}

void adc_dma_read(uint32_t *buffer)
{
ADCProcessorTrigger(ADC0_BASE, 0);
	while(!ADCIntStatus(ADC0_BASE, 0, false))
{}
ADCIntClear(ADC0_BASE, 0);
uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,UDMA_MODE_BASIC,(void *)(ADC0_BASE+ADC_O_SSFIFO0 ),buffer,8);
}
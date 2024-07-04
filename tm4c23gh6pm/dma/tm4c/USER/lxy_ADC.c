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
//������:ADC_init_SS0
//����˵������ʼ��ADCģ����������ΪSS0
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_init_SS0(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,0);
}
//**************************************************************************************
//������:ADC_init_SS1
//����˵������ʼ��ADCģ�飬��������ΪSS1
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_init_SS1(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,1);
}
//**************************************************************************************
//������:ADC_init_SS2
//����˵������ʼ��ADCģ�飬��������ΪSS2
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_init_SS2(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,2);
}
//**************************************************************************************
//������:ADC_init_SS3
//����˵������ʼ��ADCģ��
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_init_SS3(){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	GPIOPinTypeADC(PE,P_2);
	ADCSequenceEnable(ADC1_BASE,3);
}
//**************************************************************************************
//������:ADC_SS0_SET
//����˵�������òɼ�ģʽΪSS0
//�βΣ�uint32_t ui32Config�����ںţ�
//����ֵ����
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
//������:ADC_SS1_SET
//����˵�������òɼ�ģʽΪSS1
//�βΣ�uint32_t ui32Config�����ںţ�
//����ֵ����
//**************************************************************************************	
void ADC_SS1_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,1,0,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,1,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,2,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,1,3,ui32Config);

}
//**************************************************************************************
//������:ADC_SS2_SET
//����˵�������òɼ�ģʽΪSS2
//�βΣ�uint32_t ui32Config�����ںţ�
//����ֵ����
//**************************************************************************************	
void ADC_SS2_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,2,0,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,1,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,2,ui32Config);
	ADCSequenceStepConfigure(ADC1_BASE,2,3,ui32Config);

}
//**************************************************************************************
//������:ADC_SS3_SET
//����˵�������òɼ�ģʽΪSS3
//�βΣ�uint32_t ui32Config�����ںţ�
//����ֵ����
//**************************************************************************************	
void ADC_SS3_SET(uint32_t ui32Config)
{	
	ADCSequenceStepConfigure(ADC1_BASE,3,0,ui32Config|ADC_CTL_END);

}
//**************************************************************************************
//������:ADC_SS0_INT
//����˵��������ADC��SS0�µ��ж�
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_SS0_INT()
{ADCIntEnable(ADC1_BASE,0);
	IntPrioritySet(INT_ADC1SS0,0);
	IntEnable(INT_ADC1SS0);
	IntMasterEnable();
}
//**************************************************************************************
//������:ADC_SS1_INT
//����˵��������ADC��SS1�µ��ж�
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_SS1_INT()
{ADCIntEnable(ADC1_BASE,1);
	IntPrioritySet(INT_ADC1SS1,0);
	IntEnable(INT_ADC1SS1);
	IntMasterEnable();
}
//**************************************************************************************
//������:ADC_SS2_INT
//����˵��������ADC��SS2�µ��ж�
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_SS2_INT()
{ADCIntEnable(ADC1_BASE,2);
	IntPrioritySet(INT_ADC1SS2,0);
	IntEnable(INT_ADC1SS2);
	IntMasterEnable();
}
//**************************************************************************************
//������:ADC_SS3_INT
//����˵��������ADC��SS3�µ��ж�
//�βΣ���
//����ֵ����
//**************************************************************************************	
void ADC_SS3_INT()
{ADCIntEnable(ADC1_BASE,3);
	IntPrioritySet(INT_ADC1SS3,0);
	IntEnable(INT_ADC1SS3);
	IntMasterEnable();
}


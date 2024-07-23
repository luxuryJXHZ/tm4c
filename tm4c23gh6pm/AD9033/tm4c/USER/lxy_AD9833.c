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
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1);
		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3);
	NSS1;
	CLK1;
	FYS1;
	data1;
}
void delay(int t)
{SysCtlDelay(SysCtlClockGet()/3000*t);
}
//***********************************
//������:dac_sendbite
//���ܣ���SPI����һ��16λ������
//���������͵�����
//����ֵ����
//********************************************
void dac_sendbite(uint16_t a)
{ int i;
	
	FYS0;
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
	FYS1;
	CLK1;
	data1;
	
}
void AD9833_AmpSet(unsigned char amp)
{
	unsigned char i;
	unsigned int temp;
   	
	NSS0;
	temp =0x1100|amp;
	for(i=0;i<16;i++)
	{
	    CLK0;	
	   if(temp&0x8000)
	   	data1;
	   else
		data0;
		temp<<=1;
	    CLK1;
	    delay(10);
	}
	
   	NSS1;
}

/*
*********************************************************************************************************
*	�� �� ��: AD9833_WaveSeting
*	����˵��: ��SPI���߷���16��bit����
*	��    ��: 1.Freq: Ƶ��ֵ, 0.1 hz - 12Mhz
			  2.Freq_SFR: 0 �� 1
			  3.WaveMode: TRI_WAVE(���ǲ�),SIN_WAVE(���Ҳ�),SQU_WAVE(����)
			  4.Phase : ���εĳ���λ
*	�� �� ֵ: ��
*********************************************************************************************************
*/ 
void AD9833_WaveSeting(double Freq,unsigned int Freq_SFR,unsigned int WaveMode,unsigned int Phase )
{

		int frequence_LSB,frequence_MSB,Phs_data;
		double   frequence_mid,frequence_DATA;
		long int frequence_hex;

		/*********************************����Ƶ�ʵ�16����ֵ***********************************/
		frequence_mid=268435456/25;//�ʺ�25M����
		//���ʱ��Ƶ�ʲ�Ϊ25MHZ���޸ĸô���Ƶ��ֵ����λMHz ��AD9833���֧��25MHz
		frequence_DATA=Freq;
		frequence_DATA=frequence_DATA/1000000;
		frequence_DATA=frequence_DATA*frequence_mid;
		frequence_hex=frequence_DATA;  //���frequence_hex��ֵ��32λ��һ���ܴ�����֣���Ҫ��ֳ�����14λ���д���
		frequence_LSB=frequence_hex; //frequence_hex��16λ�͸�frequence_LSB
		frequence_LSB=frequence_LSB&0x3fff;//ȥ�������λ��16λ����ȥ����λ������14λ
		frequence_MSB=frequence_hex>>14; //frequence_hex��16λ�͸�frequence_HSB
		frequence_MSB=frequence_MSB&0x3fff;//ȥ�������λ��16λ����ȥ����λ������14λ

		Phs_data=Phase|0xC000;	//��λֵ
		dac_sendbite(0x0100); //��λAD9833,��RESETλΪ1
		dac_sendbite(0x2100); //ѡ������һ��д�룬B28λ��RESETλΪ1

		if(Freq_SFR==0)				  //���������õ�����Ƶ�ʼĴ���0
		{
		 	frequence_LSB=frequence_LSB|0x4000;
		 	frequence_MSB=frequence_MSB|0x4000;
			 //ʹ��Ƶ�ʼĴ���0�������
			dac_sendbite(frequence_LSB); //L14��ѡ��Ƶ�ʼĴ���0�ĵ�14λ��������
			dac_sendbite(frequence_MSB); //H14 Ƶ�ʼĴ����ĸ�14λ��������
			dac_sendbite(Phs_data);	//������λ
			//AD9833_Write(0x2000); /**����FSELECTλΪ0��оƬ���빤��״̬,Ƶ�ʼĴ���0�������**/
	    }
		if(Freq_SFR==1)				//���������õ�����Ƶ�ʼĴ���1
		{
			 frequence_LSB=frequence_LSB|0x8000;
			 frequence_MSB=frequence_MSB|0x8000;
			//ʹ��Ƶ�ʼĴ���1�������
			dac_sendbite(frequence_LSB); //L14��ѡ��Ƶ�ʼĴ���1�ĵ�14λ����
			dac_sendbite(frequence_MSB); //H14 Ƶ�ʼĴ���1Ϊ
			dac_sendbite(Phs_data);	//������λ
			//AD9833_Write(0x2800); /**����FSELECTλΪ0������FSELECTλΪ1����ʹ��Ƶ�ʼĴ���1��ֵ��оƬ���빤��״̬,Ƶ�ʼĴ���1�������**/
		}

		if(WaveMode==TRI_WAVE) //������ǲ�����
		 	dac_sendbite(0x2002); 
		if(WaveMode==SQU_WAVE)	//�����������
			dac_sendbite(0x2028); 
		if(WaveMode==SIN_WAVE)	//������Ҳ���
			dac_sendbite(0x2000); 

}
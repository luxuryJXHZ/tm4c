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
//函数名:dac_sendbite
//功能：用SPI发送一个16位的数据
//参数：发送的数据
//返回值：无
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
*	函 数 名: AD9833_WaveSeting
*	功能说明: 向SPI总线发送16个bit数据
*	形    参: 1.Freq: 频率值, 0.1 hz - 12Mhz
			  2.Freq_SFR: 0 或 1
			  3.WaveMode: TRI_WAVE(三角波),SIN_WAVE(正弦波),SQU_WAVE(方波)
			  4.Phase : 波形的初相位
*	返 回 值: 无
*********************************************************************************************************
*/ 
void AD9833_WaveSeting(double Freq,unsigned int Freq_SFR,unsigned int WaveMode,unsigned int Phase )
{

		int frequence_LSB,frequence_MSB,Phs_data;
		double   frequence_mid,frequence_DATA;
		long int frequence_hex;

		/*********************************计算频率的16进制值***********************************/
		frequence_mid=268435456/25;//适合25M晶振
		//如果时钟频率不为25MHZ，修改该处的频率值，单位MHz ，AD9833最大支持25MHz
		frequence_DATA=Freq;
		frequence_DATA=frequence_DATA/1000000;
		frequence_DATA=frequence_DATA*frequence_mid;
		frequence_hex=frequence_DATA;  //这个frequence_hex的值是32位的一个很大的数字，需要拆分成两个14位进行处理；
		frequence_LSB=frequence_hex; //frequence_hex低16位送给frequence_LSB
		frequence_LSB=frequence_LSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位
		frequence_MSB=frequence_hex>>14; //frequence_hex高16位送给frequence_HSB
		frequence_MSB=frequence_MSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位

		Phs_data=Phase|0xC000;	//相位值
		dac_sendbite(0x0100); //复位AD9833,即RESET位为1
		dac_sendbite(0x2100); //选择数据一次写入，B28位和RESET位为1

		if(Freq_SFR==0)				  //把数据设置到设置频率寄存器0
		{
		 	frequence_LSB=frequence_LSB|0x4000;
		 	frequence_MSB=frequence_MSB|0x4000;
			 //使用频率寄存器0输出波形
			dac_sendbite(frequence_LSB); //L14，选择频率寄存器0的低14位数据输入
			dac_sendbite(frequence_MSB); //H14 频率寄存器的高14位数据输入
			dac_sendbite(Phs_data);	//设置相位
			//AD9833_Write(0x2000); /**设置FSELECT位为0，芯片进入工作状态,频率寄存器0输出波形**/
	    }
		if(Freq_SFR==1)				//把数据设置到设置频率寄存器1
		{
			 frequence_LSB=frequence_LSB|0x8000;
			 frequence_MSB=frequence_MSB|0x8000;
			//使用频率寄存器1输出波形
			dac_sendbite(frequence_LSB); //L14，选择频率寄存器1的低14位输入
			dac_sendbite(frequence_MSB); //H14 频率寄存器1为
			dac_sendbite(Phs_data);	//设置相位
			//AD9833_Write(0x2800); /**设置FSELECT位为0，设置FSELECT位为1，即使用频率寄存器1的值，芯片进入工作状态,频率寄存器1输出波形**/
		}

		if(WaveMode==TRI_WAVE) //输出三角波波形
		 	dac_sendbite(0x2002); 
		if(WaveMode==SQU_WAVE)	//输出方波波形
			dac_sendbite(0x2028); 
		if(WaveMode==SIN_WAVE)	//输出正弦波形
			dac_sendbite(0x2000); 

}
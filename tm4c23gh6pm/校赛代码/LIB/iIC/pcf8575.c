#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "inc/hw_hibernate.h"
#include "driverlib/hibernate.h"
#include "driverlib/cpu.h"
#include "driverlib/timer.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/adc.h"
#include "driverlib/rom.h"
#include "pcf8575.h"



/**********************************************************************************************************
*	函 数 名: Delay5us
*	功能说明: 延时5us
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void Delay5us()
{
	SysCtlDelay(SysCtlClockGet()/1000000*5); // TM4C123G标准5um
}


/**********************************************************************************************************
*	函 数 名: I2C_Start
*	功能说明: I2C通讯时序的开始
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Start(void)
{
	SDA1;                    //拉高数据线
	SCL1;                    //拉高时钟线
	Delay5us();                 //延时
	SDA0;                    //产生下降沿
	Delay5us();                 //延时
	SCL0;                    //拉低时钟线
}


/**********************************************************************************************************
*	函 数 名: I2C_Stop
*	功能说明: I2C通讯时序的结束
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Stop(void)
{
	SDA0;                    //拉低数据线
	SCL1;                    //拉高时钟线
	Delay5us();                 //延时
	SDA1;                    //产生上升沿
	Delay5us();                 //延时
}

/**********************************************************************************************************
*	函 数 名: I2C_SendACK
*	功能说明: I2C发送应答信号
*	形    参: ack (0:ACK应答 1:NAK无应答)
*	返 回 值: 无
**********************************************************************************************************/
void I2C_SendACK(int ack)
{
	if(ack==1)
	{
		SDA1;
	}                  //写应答信号
	else
	{
		SDA0;
	}
	SCL1;                    //拉高时钟线
	Delay5us();                 //延时
	SCL0;                    //拉低时钟线
	Delay5us();                 //延时
}

//**************************************
//I2C接收应答信号
//**************************************

/**********************************************************************************************************
*	函 数 名: I2C_RecvACK
*	功能说明: I2C接收应答信号
*	形    参: 无
*	返 回 值: CY (0:ACK应答 1:NAK无应答)
**********************************************************************************************************/
int I2C_RecvACK(void)
{
	int CY=0;
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);  //设置引脚为输入,准备读取数据
	SCL1;                    //拉高时钟线
	Delay5us();                 //延时
	if(SDAr==PCF8575_SDA_PIN)
	{
		CY=1; 
	}                 //读应答信号
	else
	{
		CY=0;
	}
	SCL0;                    //拉低时钟线
	Delay5us();                 //延时
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4);//设置GPIO_PIN 为输输出
	return CY;
}

/**********************************************************************************************************
*	函 数 名: I2C_SendByte
*	功能说明: 向I2C总线发送8bit的数据
*	形    参: uint8_t dat
*	返 回 值: 无
**********************************************************************************************************/
void I2C_SendByte(uint8_t dat)
{
    int i;
    for (i=0; i<8; i++)         //8位计数器
    {
		if(dat&0x80)
		{
			SDA1;
		}
		else
		{
			SDA0;
		}
		dat<<=1;
		SCL1;
		Delay5us();
		SCL0;
		Delay5us();
	}
	I2C_RecvACK();
}


/**********************************************************************************************************
*	函 数 名: I2C_Init
*	功能说明: 初始化I2C总线
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Init(void)
{
	SysCtlDelay(1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//使能启动GPIO
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,PCF8575_SCL_PIN|PCF8575_SDA_PIN);
	SCL1;
	SDA1;
}
/**********************************************************************************************************
*	函 数 名: IO_OUTPUT_SET
*	功能说明: 设置IO口输出，参数为1个16位数，前八位代表(P07-P00),后八位代表(P17-P10)
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void IO_OUTPUT_SET(uint16_t io_out)
{
	I2C_Start();                  //起始信号
	I2C_SendByte(0x40);
	I2C_SendByte(io_out>>8&0XFF);   
	I2C_SendByte(io_out&0XFF);
	I2C_Stop();                   //发送停止信号
}

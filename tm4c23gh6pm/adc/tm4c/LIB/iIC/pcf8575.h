#ifndef  __PCF8575_H
#define  __PCF8575_H
#include <stdint.h>

/**********************************************************************************************************
*	时间：2023.8.1
*	作者: 杨君临
*	说明: PCF8575 IO扩展模块的驱动
**********************************************************************************************************/

/**********************************************************************************************************
*	其他说明：PCF8575模块VCC接5v输出电压可达3.3v
*	SCL：PF3
*	SDA：PF4
**********************************************************************************************************/

/**********************************************************************************************************
*	使用说明：P首先在main函数中使用I2C_Init()初始化I2C总线，然后使用void IO_OUTPUT_SET()设置IO口状态
*	例子：
int main(void)
{
    	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
			I2C_Init();
			while(1)
			{
			  IO_OUTPUT_SET(0x8000);
			}
		
}
此例中P07被设置为高，其余IO口均为低
**********************************************************************************************************/

//F
#define  PCF8575_SCL_PIN     GPIO_PIN_3 //PF3
#define  PCF8575_SDA_PIN     GPIO_PIN_4 //PF4

#define  SCL0 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0)
#define  SCL1 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3)
#define  SDA0 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,0)
#define  SDA1 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_PIN_4)
#define  SDAr GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(int ack);
int I2C_RecvACK(void);
void I2C_SendByte(uint8_t dat);
/**********************************************************************************************************
*	函 数 名: I2C_Init
*	功能说明: 初始化I2C总线
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Init(void);
/**********************************************************************************************************
*	函 数 名: IO_OUTPUT_SET
*	功能说明: 设置IO口输出，参数为1个16位数，前八位代表(P07-P00),后八位代表(P17-P10)
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void IO_OUTPUT_SET(uint16_t io_out);




#endif


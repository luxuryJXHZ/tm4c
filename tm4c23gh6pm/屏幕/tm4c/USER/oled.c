#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <oled.h>
#include "driverlib/cpu.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include  <font.h>
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "inc/hw_nvic.h"
#include "inc/hw_flash.h"

#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"
uint8_t OLED_GRAM[144][8];

/**********************************************************************************************************
*	函 数 名: Delay5us
*	功能说明: 延时5us
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void Delay5us()
{
	int t=3; 
		while(t--);
	// TM4C123G标准5um
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
*	函 数 名: I2C_waitack
*	功能说明: 等待应答信号
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_waitack(void)
{
	SDA1;//拉高数据线
	Delay5us();//延时
	SCL1;//拉高时钟线
	Delay5us();//延时
	SCL0;
	Delay5us();
}
/**********************************************************************************************************
*	函 数 名: I2C_SendByte
*	功能说明: 向I2C总线发送8bit的数据
*	形    参: uint8_t dat
*	返 回 值: 无
**********************************************************************************************************/
void I2C_SendByte(uint8_t dat)
{uint8_t i;
	for(i=0;i<8;i++)
	{if(dat&0x80)
		{SDA1;
		}
		else
		{SDA0;
		}
	dat<<=1;
	Delay5us();
	SCL1;
	Delay5us();
	SCL0;
	}
}
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
	if(SDAr==OLED_SDA_PIN)
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
*	函 数 名: OELD_WR_Byte
*	功能说明: 判断写的是命令还是数据
*	形    参数: uint8_t dat，mode
*	返 回 值: 无
**********************************************************************************************************/
void OLED_WR_Byte(uint8_t dat,uint8_t mode)
{I2C_Start();
	I2C_SendByte(0x78);
	I2C_waitack();
	if(mode)
	{
		I2C_SendByte(0x40);//写数据
	}
	else
	{I2C_SendByte(0x00);//写命令
	}
	I2C_waitack();
	I2C_SendByte(dat);
	I2C_waitack();
	I2C_Stop();
}
/**********************************************************************************************************
*	函 数 名: OLED_init
*	功能说明: 初始化OLED
*	形    参数: 无
*	返 回 值: 无
**********************************************************************************************************/
void OLED_init(void)
{
	res0 ;
	Delay5us();
	res1;
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_clear();
	OLED_WR_Byte(0xAF,OLED_CMD);
 

}
void OLED_ColorTurn(uint8_t i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xA6, OLED_CMD); 
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xA7, OLED_CMD); 
	}
}
void OLED_Refresh(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD); //设置行起始地址
		OLED_WR_Byte(0x00,OLED_CMD);   //设置低列起始地址
		OLED_WR_Byte(0x10,OLED_CMD);   //设置高列起始地址
		I2C_Start();
		I2C_SendByte(0x78);
		I2C_waitack();
		I2C_SendByte(0x40);
		I2C_waitack();
		for(n=0;n<128;n++)
		{
			I2C_SendByte(OLED_GRAM[n][i]);
			I2C_waitack();
		}
		I2C_Stop();
  }
}
void OLED_DisplayTurn(uint8_t i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xC8, OLED_CMD); 
		OLED_WR_Byte(0xA1, OLED_CMD);
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xC0, OLED_CMD);
		OLED_WR_Byte(0xA0, OLED_CMD);
	}
}
 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); 
	OLED_WR_Byte(0x14, OLED_CMD); 
	OLED_WR_Byte(0xAF, OLED_CMD); 
}
 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); 
	OLED_WR_Byte(0x10, OLED_CMD); 
	OLED_WR_Byte(0xAE, OLED_CMD); 
}
void OLED_clear(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
			{
			 OLED_GRAM[n][i]=0;//清除所有数据
			}
  }
	OLED_Refresh();//更新显示
}
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	if(t){OLED_GRAM[x][i]|=n;}
	else
	{
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
		OLED_GRAM[x][i]|=n;
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	}
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size1:选择字体 6x8/6x12/8x16/12x24
//mode:0,反色显示;1,正常显示
void OLEDShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(size1==8)
			  {temp=asc2_0806[chr1][i];} //调用0806字体
		else if(size1==12)
        {temp=asc2_1206[chr1][i];} //调用1206字体
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //调用1608字体
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //调用2412字体
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp>>=1;
			y++;
		}
		x++;
		if((size1!=8)&&((x-x0)==size1/2))
		{x=x0;y0=y0+8;}
		y=y0;
  }
}


//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
//mode:0,反色显示;1,正常显示
void OLEDShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLEDShowChar(x,y,*chr,size1,mode);
		if(size1==8)x+=6;
		else x+=size1/2;
		chr++;
  }
}
u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode)
{
	u8 t,temp,m=0;
	if(size1==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				OLEDShowChar(x+(size1/2+m)*t,y,'0',size1,mode);
      }
			else 
			{
			  OLEDShowChar(x+(size1/2+m)*t,y,temp+'0',size1,mode);
			}
  }
}




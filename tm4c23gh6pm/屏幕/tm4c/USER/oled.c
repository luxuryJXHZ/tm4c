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
*	�� �� ��: Delay5us
*	����˵��: ��ʱ5us
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void Delay5us()
{
	int t=3; 
		while(t--);
	// TM4C123G��׼5um
}
/**********************************************************************************************************
*	�� �� ��: I2C_Start
*	����˵��: I2CͨѶʱ��Ŀ�ʼ
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_Start(void)
{
	SDA1;                    //����������
	SCL1;                    //����ʱ����
	Delay5us();                 //��ʱ
	SDA0;                    //�����½���
	Delay5us();                 //��ʱ
	SCL0;                    //����ʱ����
}


/**********************************************************************************************************
*	�� �� ��: I2C_Stop
*	����˵��: I2CͨѶʱ��Ľ���
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_Stop(void)
{
	SDA0;                    //����������
	SCL1;                    //����ʱ����
	Delay5us();                 //��ʱ
	SDA1;                    //����������
	Delay5us();                 //��ʱ
}
/**********************************************************************************************************
*	�� �� ��: I2C_waitack
*	����˵��: �ȴ�Ӧ���ź�
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_waitack(void)
{
	SDA1;//����������
	Delay5us();//��ʱ
	SCL1;//����ʱ����
	Delay5us();//��ʱ
	SCL0;
	Delay5us();
}
/**********************************************************************************************************
*	�� �� ��: I2C_SendByte
*	����˵��: ��I2C���߷���8bit������
*	��    ��: uint8_t dat
*	�� �� ֵ: ��
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
	}                  //дӦ���ź�
	else
	{
		SDA0;
	}
	SCL1;                    //����ʱ����
	Delay5us();                 //��ʱ
	SCL0;                    //����ʱ����
	Delay5us();                 //��ʱ
}

//**************************************
//I2C����Ӧ���ź�
//**************************************

/**********************************************************************************************************
*	�� �� ��: I2C_RecvACK
*	����˵��: I2C����Ӧ���ź�
*	��    ��: ��
*	�� �� ֵ: CY (0:ACKӦ�� 1:NAK��Ӧ��)
**********************************************************************************************************/
int I2C_RecvACK(void)
{
	int CY=0;
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);  //��������Ϊ����,׼����ȡ����
	SCL1;                    //����ʱ����
	Delay5us();                 //��ʱ
	if(SDAr==OLED_SDA_PIN)
	{
		CY=1; 
	}                 //��Ӧ���ź�
	else
	{
		CY=0;
	}
	SCL0;                    //����ʱ����
	Delay5us();                 //��ʱ
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4);//����GPIO_PIN Ϊ�����
	return CY;
}
/**********************************************************************************************************
*	�� �� ��: OELD_WR_Byte
*	����˵��: �ж�д�������������
*	��    ����: uint8_t dat��mode
*	�� �� ֵ: ��
**********************************************************************************************************/
void OLED_WR_Byte(uint8_t dat,uint8_t mode)
{I2C_Start();
	I2C_SendByte(0x78);
	I2C_waitack();
	if(mode)
	{
		I2C_SendByte(0x40);//д����
	}
	else
	{I2C_SendByte(0x00);//д����
	}
	I2C_waitack();
	I2C_SendByte(dat);
	I2C_waitack();
	I2C_Stop();
}
/**********************************************************************************************************
*	�� �� ��: OLED_init
*	����˵��: ��ʼ��OLED
*	��    ����: ��
*	�� �� ֵ: ��
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
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
		OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
		OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
		OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
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
			 OLED_GRAM[n][i]=0;//�����������
			}
  }
	OLED_Refresh();//������ʾ
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

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLEDShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
		if(size1==8)
			  {temp=asc2_0806[chr1][i];} //����0806����
		else if(size1==12)
        {temp=asc2_1206[chr1][i];} //����1206����
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //����1608����
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //����2412����
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


//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
//mode:0,��ɫ��ʾ;1,������ʾ
void OLEDShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
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




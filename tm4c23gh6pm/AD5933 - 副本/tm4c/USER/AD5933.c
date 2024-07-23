#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <start.h>
#include <iic.h>
#include <math.h>
#include <AD5933.h>

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
#include "hw_uc1701.h"
#include "utils/uartstdio.h"

void  SETpoint(char nAdder)
{

	writejibyte(ntemp,0xB0,nAdder);
	SysCtlDelay(100);
}

uint8_t  rece_byte(char naddr)
{
   uint8_t x;
	SETpoint(naddr);
	x=I2CReadBYTE(ntemp);
	return x;
}

void Maopao_Paixu(float *dat, uint16_t leng)
{
    uint16_t  i, j;
    float buf;
    for(j = 0; j < leng - 1; j++)
        for(i = 0; i < leng - j - 1; i++)
            if(dat[i] > dat[i + 1])
            {
                buf = dat[i];
                dat[i] = dat[i + 1];
                dat[i + 1] = buf;
            }
}




uint32_t Scale_imp (uint8_t  *SValue, uint8_t *IValue, uint8_t *NValue, uint8_t *CValue)
{
    uint32_t ReadTemp, realArr[3], imageArr[3],sum;
    uint16_t repCnt = 1;
    int i, j, AddrTemp;
	  uint32_t resistance=0;
    uint8_t Gain = ((~CValue[0]) & 0x01) ? 5 : 1;
    uint8_t SWeep_Rep = ((CValue[0] & 0xF0) == (AD5933_Fre_UP >> 8)) ? 1 : 0;
    uint8_t Mode = CValue[0] & 0x0f;
    uint16_t tan;
    uint32_t   magnitude;
    j = 0;
    InitI2C1();    //初始化I2C
    AddrTemp=0X82; //初始化起始频率寄存器
    /*for(i = 0; i < 3; i++)
    {
        writejibyte(ntemp,AddrTemp,SValue [i]);
        AddrTemp++;
    }
    AddrTemp=0X85; //初始化频率增量寄存器
    for(i = 0; i < 3; i++)
    {
        writejibyte(ntemp ,AddrTemp, IValue[i]);
        AddrTemp++;
    }
    AddrTemp = 0X88; //初始化频率点数寄存器
    for(i = 0; i < 2; i++)
    {
        writejibyte(ntemp ,AddrTemp, NValue[i]);
        AddrTemp++;
    }
*/
    // Transmit to settling time cycles register (沉降时间周期数)
    // program 15 output cycles at each frequency before a adc conversion
		
/*
    //初始化控制寄存器
    AddrTemp = 0X80;
                  //for(i = 0;i <2;i++)
{
        writejibyte(ntemp ,AddrTemp, Mode | (AD5933_Standby >> 8));
        AddrTemp++;
        writejibyte(ntemp ,AddrTemp, 0x00);
        AddrTemp++;
}   

    writejibyte(ntemp ,0x80, Mode | (AD5933_SYS_Init >> 8)); //控制寄存器写入初始化频率扫描命令
		//writejibyte(ntemp ,0x80, 0x11);
    SysCtlDelay(SysCtlClockGet ()/3000*10);
		writejibyte(ntemp ,0X80, Mode | (AD5933_Begin_Fre_Scan >> 8)); //控制寄存器写入开始频率扫描命令
   //writejibyte(ntemp ,0X80, 0x21);*/
	 
	 		writejibyte(ntemp,0x82,0x0F);
		writejibyte(ntemp,0x83,0x5C);
		writejibyte(ntemp,0x84,0x28);//30khz
		writejibyte(ntemp,0x85,0x00);
		writejibyte(ntemp,0x86,0x01);
		writejibyte(ntemp,0x87,0x4F);//10hz步进
		writejibyte(ntemp,0x88,0x00);
		writejibyte(ntemp,0x89,10);
		
    writejibyte(ntemp ,0x8B, 15);
    writejibyte(ntemp , 0x8A, 0x02);//建立周期
		
		
    writejibyte(ntemp ,0x80, 0xB0|data_Vpp|data_gain);
		writejibyte(ntemp ,0x81, 0x10|data_clk );
		SysCtlDelay (SysCtlClockGet ()/3000*150);
		writejibyte(ntemp ,0x81,  0x00|data_clk);
		writejibyte(ntemp ,0x80, 0x10|data_Vpp|data_gain);
			SysCtlDelay (SysCtlClockGet ()/3000*30);
		writejibyte(ntemp ,0x80, 0x20|data_Vpp|data_gain);


    while(1)
    {
        while(1)
        {
            ReadTemp = rece_byte(0x8F); //读取状态寄存器检查DFT是否完成
            if (ReadTemp & 0x02)
                break;
        }
        realArr[0] = rece_byte(0x94);
				realArr[0] = rece_byte(0x94);
        realArr[1] = rece_byte(0x95);
				realArr[1] = rece_byte(0x95);
        realArr[2] = realArr[0] * 0x100 + realArr[1];
     //   realArr[2] = realArr[0] + realArr[1] * 0x100;
        imageArr[0] = rece_byte(0x96);
				     imageArr[0] = rece_byte(0x96);
        imageArr[1] = rece_byte(0x97);
				imageArr[1] = rece_byte(0x97);
        imageArr[2] = imageArr[0] * 0x100 + imageArr[1];
   // imageArr[2] = imageArr[0]  + imageArr[1]* 0x100;
        if (realArr[2] >= 0x8000) //计算实部的原码(除符号位外，取反加一)
        {
            realArr[2] ^= 0xFFFF;
            realArr[2] ^= 0x8000;
            realArr[2] += 1;
            realArr[2] ^= 0x8000;
        }
        if (imageArr[2] >= 0x8000) //计算虚部的原码(除符号位外，取反加一)
        {
            imageArr[2] ^= 0xFFFF;
            imageArr[2] ^= 0x8000;
            imageArr[2] += 1;
            imageArr[2] ^= 0x8000;
        }
        magnitude=sqrt(realArr[2] * realArr[2]*100+ imageArr[2] * imageArr[2]*100); //模值计算
        resistance= magnitude+resistance;		 //阻抗计算累加计算
        tan=imageArr [2]*1000/realArr[2];
      ReadTemp = rece_byte(0x8F); //读取状态寄存器检查频率扫描是否完成
        if (ReadTemp & 0x04)
            break;
				if(repCnt ==50)
					break;
        if (SWeep_Rep == 1)		//频率递增扫描模式
        {    repCnt ++;
					
            writejibyte(ntemp ,0X80, 0x31);	//控制寄存器写入增加频率（跳到下一个频率点)的命令
        }
        else		//频率重复模式
        {
            repCnt++;
            if(repCnt >= *NValue)
            {
                break;
            }
            writejibyte(ntemp ,0X80, CValue[0]);	//控制寄存器写入重复
						//当前频率点扫描
        }
    }
    resistance=resistance/repCnt; 
		
    return resistance;
}


float Get_AVE(float src[], uint16_t num)
{
    uint16_t  i, cnt = 0;
    float sum;
    Maopao_Paixu(src, num);

    sum = 0;
    for(i = num / 2 - num / 4; i < num / 2 + num / 4; i++)
    {
        sum += src[i];
        cnt++;
    }
    sum = sum / cnt;
    return sum;
}
void Fre_To_Hex(float fre, uint8_t  *buf)
{
    uint32_t  dat;
    dat = (536870912 / (double)(AD5933_MCLK * 1000000)) * fre;

    buf[0] = dat >> 16;
    buf[1] = dat >> 8;
    buf[2] = dat;

}

/*
函数名：	AD5933_Sweep
功  能：	频率扫描。按设定的频率起点，频率步进，步数及输出幅值，进行增量扫描或重复频率扫描，经内部gain增益后采集实部，虚部，换算阻抗值
输  入：		Fre_Begin 		开始频率；(范围：1k~100k Hz， 精度0.1Hz)
					Fre_UP				步进频率；(范围：1k~100k Hz， 精度0.1Hz)
					UP_Num				步进次数；(范围：0~511)
					OUTPUT_Vatage	输出电压；(范围：AD5933_OUTPUT_2V/AD5933_OUTPUT_1V/AD5933_OUTPUT_400mV/AD5933_OUTPUT_200mV)
					Gain： 				内部增益(范围：AD5933_Gain_1/AD5933_Gain_5)
					SWeep_Rep			扫描模式(范围：AD5933_Fre_UP:递增频率扫描；AD5933_Fre_Rep：重复频率扫描)
输  出：		R_Impedance：	电阻值；
					realData：		实部数据；
					imageData：		虚部数据；
注  释：无
*/
uint32_t AD5933_Sweep (float Fre_Begin, float Fre_UP, uint16_t UP_Num, uint16_t OUTPUT_Vatage, uint16_t Gain, uint16_t SWeep_Rep)
{
    uint8_t   SValue[3], IValue[3], NValue[2], CValue[2];
    uint16_t  buf = 0;
	uint32_t x;
    Fre_To_Hex(Fre_Begin, SValue);
    Fre_To_Hex(Fre_UP, IValue);
    NValue[0] = UP_Num >> 8;
    NValue[1] = UP_Num;
#if AD5933_MCLK_USE_OUT == 1
    buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_OUT_MCLK;
#else
    buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_IN_MCLK;
#endif
    CValue[0] = buf >> 8;
    CValue[1] = buf;

 x=Scale_imp(SValue, IValue, NValue, CValue);
	
    return x;
}
/*SValue[3]起始频率，IValue[3]频率增量，NValue[2]增量数，CValue[2]控制字，ki增益系数，Ps扫频为1重复为0*/


/*
函数名：	DA5933_Get_RsRealImage
功  能：	获得所夹持电阻的阻值，及测得的实部数据及虚部数据
输  入：无
输  出：R_Impedance：电阻值；	realData：实部数据；	imageData：虚部数据；
注  释：无
*/
uint32_t DA5933_Get_RsRealImage()
{
    uint32_t RsWord=0, ReWord, ImWord;
     uint32_t r[swpPNTCnt];
	int i;
		//从频率10240Hz开始扫描，1Hz步进，扫描swpPNTCnt步，输出幅度2V，增益1,扫描模式
   RsWord = AD5933_Sweep(1024,256,swpPNTCnt, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP) ;
		
	
    //RsWord = Get_AVE(resistance,    swpPNTCnt);	//阻抗数据的结果都存放在数组resistance， 从该数组求一个均值
    //ReWord = Get_AVE(AD5933_Dat_Re, swpPNTCnt);	//实部数据的结果都存放在数AD5933_Dat_Re，从该数组求一个均值
    //ImWord = Get_AVE(AD5933_Dat_Im, swpPNTCnt);	//虚部数据的结果都存放在数AD5933_Dat_Im，从该数组求一个均值
	//RsWord =99568480/RsWord;
	  RsWord =9982980/RsWord;
	RsWord =1000000000000/(31550*RsWord*6.28);
	
		//注
		//AD5933测量值时，模值数据与电阻值具有一定的非线性，校准方法较多，一般比较简单的可采用多线段校正(也可用其他方法)
		//RsWord即为所测得阻抗模值，用户可利用该数据进行多线段校正，如分别记录5k，10k，50k，100k，500k时RsWord的值，
		//后续测得RsWord值时，找到RsWord值在哪个区间及其位置，再将值线性对应到该位置对应的阻值
		//下述例程为仅以10k标准电阻校准的简单校准方法，用户需更大范围或更准确数值时，可参考上述或其他方法
	
//    *R_Impedance = RsWord ;	//阻抗数据乘以一个校准因子，得到电阻值
//    *realData = ReWord;
//    *imageData = ImWord;

 return RsWord;
}
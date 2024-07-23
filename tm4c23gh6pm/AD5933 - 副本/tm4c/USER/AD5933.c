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
    InitI2C1();    //��ʼ��I2C
    AddrTemp=0X82; //��ʼ����ʼƵ�ʼĴ���
    /*for(i = 0; i < 3; i++)
    {
        writejibyte(ntemp,AddrTemp,SValue [i]);
        AddrTemp++;
    }
    AddrTemp=0X85; //��ʼ��Ƶ�������Ĵ���
    for(i = 0; i < 3; i++)
    {
        writejibyte(ntemp ,AddrTemp, IValue[i]);
        AddrTemp++;
    }
    AddrTemp = 0X88; //��ʼ��Ƶ�ʵ����Ĵ���
    for(i = 0; i < 2; i++)
    {
        writejibyte(ntemp ,AddrTemp, NValue[i]);
        AddrTemp++;
    }
*/
    // Transmit to settling time cycles register (����ʱ��������)
    // program 15 output cycles at each frequency before a adc conversion
		
/*
    //��ʼ�����ƼĴ���
    AddrTemp = 0X80;
                  //for(i = 0;i <2;i++)
{
        writejibyte(ntemp ,AddrTemp, Mode | (AD5933_Standby >> 8));
        AddrTemp++;
        writejibyte(ntemp ,AddrTemp, 0x00);
        AddrTemp++;
}   

    writejibyte(ntemp ,0x80, Mode | (AD5933_SYS_Init >> 8)); //���ƼĴ���д���ʼ��Ƶ��ɨ������
		//writejibyte(ntemp ,0x80, 0x11);
    SysCtlDelay(SysCtlClockGet ()/3000*10);
		writejibyte(ntemp ,0X80, Mode | (AD5933_Begin_Fre_Scan >> 8)); //���ƼĴ���д�뿪ʼƵ��ɨ������
   //writejibyte(ntemp ,0X80, 0x21);*/
	 
	 		writejibyte(ntemp,0x82,0x0F);
		writejibyte(ntemp,0x83,0x5C);
		writejibyte(ntemp,0x84,0x28);//30khz
		writejibyte(ntemp,0x85,0x00);
		writejibyte(ntemp,0x86,0x01);
		writejibyte(ntemp,0x87,0x4F);//10hz����
		writejibyte(ntemp,0x88,0x00);
		writejibyte(ntemp,0x89,10);
		
    writejibyte(ntemp ,0x8B, 15);
    writejibyte(ntemp , 0x8A, 0x02);//��������
		
		
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
            ReadTemp = rece_byte(0x8F); //��ȡ״̬�Ĵ������DFT�Ƿ����
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
        if (realArr[2] >= 0x8000) //����ʵ����ԭ��(������λ�⣬ȡ����һ)
        {
            realArr[2] ^= 0xFFFF;
            realArr[2] ^= 0x8000;
            realArr[2] += 1;
            realArr[2] ^= 0x8000;
        }
        if (imageArr[2] >= 0x8000) //�����鲿��ԭ��(������λ�⣬ȡ����һ)
        {
            imageArr[2] ^= 0xFFFF;
            imageArr[2] ^= 0x8000;
            imageArr[2] += 1;
            imageArr[2] ^= 0x8000;
        }
        magnitude=sqrt(realArr[2] * realArr[2]*100+ imageArr[2] * imageArr[2]*100); //ģֵ����
        resistance= magnitude+resistance;		 //�迹�����ۼӼ���
        tan=imageArr [2]*1000/realArr[2];
      ReadTemp = rece_byte(0x8F); //��ȡ״̬�Ĵ������Ƶ��ɨ���Ƿ����
        if (ReadTemp & 0x04)
            break;
				if(repCnt ==50)
					break;
        if (SWeep_Rep == 1)		//Ƶ�ʵ���ɨ��ģʽ
        {    repCnt ++;
					
            writejibyte(ntemp ,0X80, 0x31);	//���ƼĴ���д������Ƶ�ʣ�������һ��Ƶ�ʵ�)������
        }
        else		//Ƶ���ظ�ģʽ
        {
            repCnt++;
            if(repCnt >= *NValue)
            {
                break;
            }
            writejibyte(ntemp ,0X80, CValue[0]);	//���ƼĴ���д���ظ�
						//��ǰƵ�ʵ�ɨ��
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
��������	AD5933_Sweep
��  �ܣ�	Ƶ��ɨ�衣���趨��Ƶ����㣬Ƶ�ʲ����������������ֵ����������ɨ����ظ�Ƶ��ɨ�裬���ڲ�gain�����ɼ�ʵ�����鲿�������迹ֵ
��  �룺		Fre_Begin 		��ʼƵ�ʣ�(��Χ��1k~100k Hz�� ����0.1Hz)
					Fre_UP				����Ƶ�ʣ�(��Χ��1k~100k Hz�� ����0.1Hz)
					UP_Num				����������(��Χ��0~511)
					OUTPUT_Vatage	�����ѹ��(��Χ��AD5933_OUTPUT_2V/AD5933_OUTPUT_1V/AD5933_OUTPUT_400mV/AD5933_OUTPUT_200mV)
					Gain�� 				�ڲ�����(��Χ��AD5933_Gain_1/AD5933_Gain_5)
					SWeep_Rep			ɨ��ģʽ(��Χ��AD5933_Fre_UP:����Ƶ��ɨ�裻AD5933_Fre_Rep���ظ�Ƶ��ɨ��)
��  ����		R_Impedance��	����ֵ��
					realData��		ʵ�����ݣ�
					imageData��		�鲿���ݣ�
ע  �ͣ���
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
/*SValue[3]��ʼƵ�ʣ�IValue[3]Ƶ��������NValue[2]��������CValue[2]�����֣�ki����ϵ����PsɨƵΪ1�ظ�Ϊ0*/


/*
��������	DA5933_Get_RsRealImage
��  �ܣ�	������гֵ������ֵ������õ�ʵ�����ݼ��鲿����
��  �룺��
��  ����R_Impedance������ֵ��	realData��ʵ�����ݣ�	imageData���鲿���ݣ�
ע  �ͣ���
*/
uint32_t DA5933_Get_RsRealImage()
{
    uint32_t RsWord=0, ReWord, ImWord;
     uint32_t r[swpPNTCnt];
	int i;
		//��Ƶ��10240Hz��ʼɨ�裬1Hz������ɨ��swpPNTCnt�����������2V������1,ɨ��ģʽ
   RsWord = AD5933_Sweep(1024,256,swpPNTCnt, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP) ;
		
	
    //RsWord = Get_AVE(resistance,    swpPNTCnt);	//�迹���ݵĽ�������������resistance�� �Ӹ�������һ����ֵ
    //ReWord = Get_AVE(AD5933_Dat_Re, swpPNTCnt);	//ʵ�����ݵĽ�����������AD5933_Dat_Re���Ӹ�������һ����ֵ
    //ImWord = Get_AVE(AD5933_Dat_Im, swpPNTCnt);	//�鲿���ݵĽ�����������AD5933_Dat_Im���Ӹ�������һ����ֵ
	//RsWord =99568480/RsWord;
	  RsWord =9982980/RsWord;
	RsWord =1000000000000/(31550*RsWord*6.28);
	
		//ע
		//AD5933����ֵʱ��ģֵ���������ֵ����һ���ķ����ԣ�У׼�����϶࣬һ��Ƚϼ򵥵Ŀɲ��ö��߶�У��(Ҳ������������)
		//RsWord��Ϊ������迹ģֵ���û������ø����ݽ��ж��߶�У������ֱ��¼5k��10k��50k��100k��500kʱRsWord��ֵ��
		//�������RsWordֵʱ���ҵ�RsWordֵ���ĸ����估��λ�ã��ٽ�ֵ���Զ�Ӧ����λ�ö�Ӧ����ֵ
		//��������Ϊ����10k��׼����У׼�ļ�У׼�������û������Χ���׼ȷ��ֵʱ���ɲο���������������
	
//    *R_Impedance = RsWord ;	//�迹���ݳ���һ��У׼���ӣ��õ�����ֵ
//    *realData = ReWord;
//    *imageData = ImWord;

 return RsWord;
}
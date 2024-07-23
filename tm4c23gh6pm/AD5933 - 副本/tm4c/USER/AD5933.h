#ifndef AD5933_H
#define AD5933_H
#include <stdint.h>
#define ntemp										 0x0D

#define AD5933_SYS_Init					(1)<<12
#define AD5933_Begin_Fre_Scan		(2)<<12
#define AD5933_Fre_UP						(3)<<12
#define AD5933_Fre_Rep					(4)<<12
#define AD5933_Get_Temp					(9)<<12
#define AD5933_Sleep						(10)<<12
#define AD5933_Standby					(11)<<12

#define AD5933_OUTPUT_2V				(0)<<9
#define AD5933_OUTPUT_1V				(3)<<9
#define AD5933_OUTPUT_400mV			(2)<<9
#define AD5933_OUTPUT_200mV			(1)<<9

#define AD5933_Gain_1						(1)<<8
#define AD5933_Gain_5						(0)<<8

#define AD5933_IN_MCLK					(0)<<3
#define AD5933_OUT_MCLK					(1)<<3

#define AD5933_Reset						(1)<<4
#define AD5933 1
#define AD5933_MCLK 16.776
#define swpPNTCnt   10
#define data_clk         0x00
#define data_gain         0x01

#define data_Vpp         0x00

void  SETpoint(char nAdder);
uint8_t  rece_byte(char naddr);
void Maopao_Paixu(float *dat, uint16_t  leng);
float Get_AVE(float src[], uint16_t num);
void Fre_To_Hex(float fre, uint8_t  *buf);
uint32_t AD5933_Sweep (float Fre_Begin, float Fre_UP, uint16_t UP_Num, uint16_t OUTPUT_Vatage, uint16_t Gain, uint16_t SWeep_Rep);
uint32_t DA5933_Get_RsRealImage();
uint32_t Scale_imp (uint8_t  *SValue, uint8_t *IValue, uint8_t *NValue, uint8_t *CValue);
#endif

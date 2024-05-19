#include <stdint.h>
#ifndef lxy_ADC_H
#define lxy_ADC_H

extern void ADC_init_SS0();
extern void ADC_init_SS1();
extern void ADC_init_SS2();
extern void ADC_init_SS3();
extern void ADC_SS0_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS1_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS2_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS3_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS0_INT();
extern void ADC_SS1_INT();
extern void ADC_SS2_INT();
extern void ADC_SS3_INT();


#endif
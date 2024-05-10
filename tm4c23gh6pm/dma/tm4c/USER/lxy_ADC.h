#include <stdint.h>
#ifndef lxy_ADC_H
#define lxy_ADC_H

extern void ADC_init_SS0(void);
extern void ADC_init_SS1(void);
extern void ADC_init_SS2(void);
extern void ADC_init_SS3(void);
extern void ADC_SS0_SET(uint32_t ui32Config);
extern void ADC_SS1_SET(uint32_t ui32Config);
extern void ADC_SS2_SET(uint32_t ui32Config);
extern void ADC_SS3_SET(uint32_t ui32Config);
extern void ADC_SS0_INT(void);
extern void ADC_SS1_INT(void);
extern void ADC_SS2_INT(void);
extern void ADC_SS3_INT(void);


#endif
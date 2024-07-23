#include <stdint.h>
#ifndef lxy_ADC_H
#define lxy_ADC_H

static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

extern void ADC_init_SS0(void);
extern void ADC_init_SS1(void);
extern void ADC_init_SS2(void);
extern void ADC_init_SS3(void);
extern void ADC_SS0_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS1_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS2_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS3_SET(uint32_t ui32Trigger,uint32_t ui32Config);
extern void ADC_SS0_INT(void);
extern void ADC_SS1_INT(void);
extern void ADC_SS2_INT(void);
extern void ADC_SS3_INT(void);
extern void secernprintf(char *str,int x);
extern void dma_adc_init(uint32_t ui32Port, uint8_t ui8Pins,uint32_t ui32Config,uint32_t *buffer);
extern void adc_dma_read(uint32_t *buffer);
#endif

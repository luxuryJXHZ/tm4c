#ifndef  __BSP_ADC_H__
#define  __BSP_ADC_H__

#include <stdint.h>

#define ADC_SAMPLE_BUF_SIZE     1000

extern uint16_t ADCBuffer1[ADC_SAMPLE_BUF_SIZE];
extern uint16_t ADCBuffer2[ADC_SAMPLE_BUF_SIZE];

void bsp_InitAdc0(void);

#endif


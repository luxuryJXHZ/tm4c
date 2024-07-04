 #ifndef MY_ADC_H
#define MY_ADC_H
 #include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/cpu.h"

#include "uc1701.h"
#include "hw_uc1701.h"
#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "pin_map.h"
#include "uartstdio.h"
#include "sysctl.h"
#include "hw_ints.h"

#include "inc/hw_adc.h"
#include "driverlib/adc.h"
#include "pcf8575.h"

#include "driverlib/udma.h"

 static uint8_t sDMAControlTable[1024] __attribute__ ((aligned(1024)));
static uint8_t sDMAControlTable[1024];



extern void ADC0_D0(void );
extern uint32_t ADC0_D0_Read(uint32_t   *pui32ADC1Value);
extern int  My_Printf(uint32_t *m,uint32_t *n,double c,int a,int b);
extern void ADC0_DMA_Init(uint32_t   *pui32ADC1Value);
uint32_t ADC0DO_DMARead(uint32_t *pui32ADC1Value);

extern void ADC1_D0(void );
extern uint32_t ADC1_D0_Read(uint32_t   *pui32ADC1Value);
extern void ADC1_DMA_Init(uint32_t   *pui32ADC1Value);
extern uint32_t ADC1_DO_DMARead(uint32_t   *pui32ADC1Value1,uint32_t   *pui32ADC1Value0);
#endif 

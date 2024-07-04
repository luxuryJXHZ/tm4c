#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <time0.h>

#include "inc/hw_udma.h"
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
#include "inc/hw_pwm.h"
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
#include "driverlib/pwm.h"
#include "driverlib/udma.h"
#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"
#define ADC_SAMPLE_BUF_SIZE  1024
int sum;
int i;
int k;
enum BUFFER_STATUS
{
    EMPTY,
    FILLING,
    FULL
};

//dma控制块需要1024字节对齐
static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

uint16_t ADCBuffer1[ADC_SAMPLE_BUF_SIZE];
uint16_t ADCBuffer2[ADC_SAMPLE_BUF_SIZE];

static enum BUFFER_STATUS BufferStatus[2];


//ADC队列3中断函数
uint32_t adc_int_count = 0;  //记录中断次数
void ADC0SS3_Handler(void)
{
    adc_int_count++;
    HWREG(ADC0_BASE + ADC_O_ISC) = HWREG(ADC0_BASE + ADC_O_RIS) & (1 << 8); //清中断

    //判断哪个buffer满了，进行切换
    if ((uDMAChannelModeGet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT) ==
                            UDMA_MODE_STOP) && (BufferStatus[0] == FILLING)) {
        BufferStatus[0] = FULL;
        BufferStatus[1] = FILLING;
    } else if ((uDMAChannelModeGet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT) ==
                                 UDMA_MODE_STOP) && (BufferStatus[1] == FILLING)) {
        BufferStatus[0] = FILLING;
        BufferStatus[1] = FULL;
    }
    
    if(BufferStatus[0] == FULL) {
        BufferStatus[0] = EMPTY;
        //使能另一个传输块
        uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                               ADCBuffer1, ADC_SAMPLE_BUF_SIZE);
        //启动DMA通道
        uDMAChannelEnable(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT);
    } else if(BufferStatus[1] == FULL) {

        BufferStatus[1] = EMPTY;

        uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                               ADCBuffer2, ADC_SAMPLE_BUF_SIZE);
        uDMAChannelEnable(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT);
    }
}

char str[20];
void ADC_V();
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	PWM_init();
	PWM_duty( PWM1_BASE, PWM_OUT_6, PWM_OUT_6_BIT, PWM_GEN_3, 0.5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	ADC_init_SS3();
	//udma配置 配置adc1，SS3序列
	uDMAEnable();
    uDMAControlBaseSet(ControlTable); 
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC1,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY |
                                UDMA_ATTR_REQMASK);
    uDMAChannelControlSet(UDMA_CHANNEL_ADC1 | UDMA_PRI_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    uDMAChannelControlSet(UDMA_CHANNEL_ADC1 | UDMA_ALT_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC1 | UDMA_PRI_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC1_BASE + ADC_O_SSFIFO3),
                           ADCBuffer1, ADC_SAMPLE_BUF_SIZE);
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC0_BASE + ADC_O_SSFIFO3),
                           ADCBuffer2, ADC_SAMPLE_BUF_SIZE);
    uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC1, UDMA_ATTR_USEBURST);
    uDMAChannelEnable(UDMA_CHANNEL_ADC1);
	
	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
	ADCSequenceConfigure(ADC1_BASE,3,ADC_TRIGGER_TIMER,1);
	ADC_SS3_SET(ADC_CTL_CH1);
	ADCSequenceDMAEnable (ADC1_BASE,3);
  ADCIntEnableEx(ADC1_BASE,ADC_INT_DMA_SS3 );
   ADCIntRegister(ADC1_BASE,3,ADC0SS3_Handler ); 
	IntEnable(INT_ADC1SS3);
													 
	TimerLoadSet(TIMER1_BASE,TIMER_B,SysCtlClockGet()*4000-1);
	TimerIntEnable(TIMER1_BASE,TIMER_TIMB_TIMEOUT);
	TimerEnable (TIMER1_BASE,TIMER_B );
	IntMasterEnable();
	
	while(1)
	{ 	
	  
	}	
		
		}	

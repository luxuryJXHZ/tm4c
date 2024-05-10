#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>

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
#define ADC_SAMPLE_BUF_SIZE 1024
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


//ADC队列0中断函数
uint32_t adc_int_count = 0;  //记录中断次数
void ADC0SS0_Handler(void)
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

int main()
{
    BufferStatus[0] = FILLING;
    BufferStatus[1] = EMPTY;
		SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
    //使能外设时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    
    //GPIO配置
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    
    uDMAEnable();
    uDMAControlBaseSet(ControlTable); //设置控制块
    
    //清除通道属性
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY |
                                UDMA_ATTR_REQMASK);
                                
    //配置主控制块参数，16位数据宽度、源地址不自增、目标地址16bit自增、每次都触发。
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
                          
    //配置副控制块参数，16位数据宽度、源地址不自增、目标地址16bit自增、每次都触发。
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
                          
    //主控制块发送设置，ping-pong模式、源地址(void *)(ADC0_BASE + ADC_O_SSFIFO0)、
    //目标地址ADCBuffer1、传输大小ADC_SAMPLE_BUF_SIZE
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                           ADCBuffer1, ADC_SAMPLE_BUF_SIZE);

    //副控制块发送设置，ping-pong模式、源地址(void *)(ADC0_BASE + ADC_O_SSFIFO0)、
    //目标地址ADCBuffer2、传输大小ADC_SAMPLE_BUF_SIZE
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                           ADCBuffer2, ADC_SAMPLE_BUF_SIZE);
    //设置连续传输
    uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC0, UDMA_ATTR_USEBURST);
    //开启DMA通道
    uDMAChannelEnable(UDMA_CHANNEL_ADC0);

    //  ADC0时钟配置 全速1M  PIOSC为16M时钟
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
    //等待时钟配置
    SysCtlDelay(10);
                           
    //关闭队列0中断
    IntDisable(INT_ADC0SS0);
    ADCIntDisable(ADC0_BASE, 0);

    //关闭队列0
    ADCSequenceDisable(ADC0_BASE, 0);

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0);  //定时器触发
//    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_ALWAYS, 0); //连续不断采样 全速

    //队列0，编号0，通道ch0|最后一个采样通道
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_END);
    //使能队列0
    ADCSequenceEnable(ADC0_BASE, 0);

    //使能队列0的dma
    ADCSequenceDMAEnable(ADC0_BASE, 0);

    //开启队列0的dma传输完成中断
    ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS0);
    
    //开启队列0中断控制器
    IntEnable(INT_ADC0SS0);
    
    //使能处理器中断控制器
    IntMasterEnable();
    
    //定时器配置
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    //16k频率
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/16000) - 1);
    //使能定时器A触发
    TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
		TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
			TimerIntRegister(TIMER0_BASE,TIMER_A,ADC0SS0_Handler);
    //使能定时器
    TimerEnable(TIMER0_BASE, TIMER_A);
		
		while(1)
		{
		}
}

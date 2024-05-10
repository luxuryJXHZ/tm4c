#include "bsp.h"

enum BUFFER_STATUS
{
    EMPTY,
    FILLING,
    FULL
};

//dma���ƿ���Ҫ1024�ֽڶ���
static uint8_t ControlTable[1024] __attribute__ ((aligned(1024)));

uint16_t ADCBuffer1[ADC_SAMPLE_BUF_SIZE];
uint16_t ADCBuffer2[ADC_SAMPLE_BUF_SIZE];

static enum BUFFER_STATUS BufferStatus[2];


//ADC����0�жϺ���
uint32_t adc_int_count = 0;  //��¼�жϴ���
void ADC0SS0_Handler(void)
{
    adc_int_count++;
    HWREG(ADC0_BASE + ADC_O_ISC) = HWREG(ADC0_BASE + ADC_O_RIS) & (1 << 8); //���ж�

    //�ж��ĸ�buffer���ˣ������л�
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
        //ʹ����һ�������
        uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                               ADCBuffer1, ADC_SAMPLE_BUF_SIZE);
        //����DMAͨ��
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

void bsp_InitAdc0(void)
{
    BufferStatus[0] = FILLING;
    BufferStatus[1] = EMPTY;
    
    //ʹ������ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    
    //GPIO����
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    
    uDMAEnable();
    uDMAControlBaseSet(ControlTable); //���ÿ��ƿ�
    
    //���ͨ������
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY |
                                UDMA_ATTR_REQMASK);
                                
    //���������ƿ������16λ���ݿ��ȡ�Դ��ַ��������Ŀ���ַ16bit������ÿ�ζ�������
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
                          
    //���ø����ƿ������16λ���ݿ��ȡ�Դ��ַ��������Ŀ���ַ16bit������ÿ�ζ�������
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT, UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
                          
    //�����ƿ鷢�����ã�ping-pongģʽ��Դ��ַ(void *)(ADC0_BASE + ADC_O_SSFIFO0)��
    //Ŀ���ַADCBuffer1�������СADC_SAMPLE_BUF_SIZE
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                           ADCBuffer1, ADC_SAMPLE_BUF_SIZE);

    //�����ƿ鷢�����ã�ping-pongģʽ��Դ��ַ(void *)(ADC0_BASE + ADC_O_SSFIFO0)��
    //Ŀ���ַADCBuffer2�������СADC_SAMPLE_BUF_SIZE
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *)(ADC0_BASE + ADC_O_SSFIFO0),
                           ADCBuffer2, ADC_SAMPLE_BUF_SIZE);
    //������������
    uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC0, UDMA_ATTR_USEBURST);
    //����DMAͨ��
    uDMAChannelEnable(UDMA_CHANNEL_ADC0);

    //  ADC0ʱ������ ȫ��1M  PIOSCΪ16Mʱ��
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
    //�ȴ�ʱ������
    SysCtlDelay(10);
                           
    //�رն���0�ж�
    IntDisable(INT_ADC0SS0);
    ADCIntDisable(ADC0_BASE, 0);

    //�رն���0
    ADCSequenceDisable(ADC0_BASE, 0);

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0);  //��ʱ������
//    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_ALWAYS, 0); //�������ϲ��� ȫ��

    //����0�����0��ͨ��ch0|���һ������ͨ��
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_END);
    //ʹ�ܶ���0
    ADCSequenceEnable(ADC0_BASE, 0);

    //ʹ�ܶ���0��dma
    ADCSequenceDMAEnable(ADC0_BASE, 0);

    //��������0��dma��������ж�
    ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS0);
    
    //��������0�жϿ�����
    IntEnable(INT_ADC0SS0);
    
    //ʹ�ܴ������жϿ�����
    IntMasterEnable();
    
    //��ʱ������
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    //16kƵ��
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SystemCoreClock/16000) - 1);
    //ʹ�ܶ�ʱ��A����
    TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
    //ʹ�ܶ�ʱ��
    TimerEnable(TIMER0_BASE, TIMER_A);
}




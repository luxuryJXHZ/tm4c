#include "bsp.h"



int main(void) 
{
    /* 初始化系统时钟为120M */
    SystemCoreClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                      SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000); //TM4C123 canot use this function
    bsp_InitDWT();
    bsp_InitLed();
    bsp_InitAdc0();
    while (1) {
        
    }
}

#include "bsp.h"


void bsp_InitLed(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4); //D3
}

inline void Led3_SetOn(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

inline void Led3_SetOff(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
}

inline void Led3_Toggle(void)
{
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        Led3_SetOff();
    else
        Led3_SetOn();
}

#include <stdint.h>
#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <adc.h>


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

#include "uc1701.h"
#include "hw_uc1701.h"
#ifndef lxy_dac_H
#define lxy_dac_H
#define NSS1 GPIOPinWrite(PF,P_1,P_1)
#define NSS0 GPIOPinWrite(PF,P_1,0)
#define CLK1 GPIOPinWrite(PD,P_0,P_0)
#define CLK0 GPIOPinWrite(PD,P_0,0)
#define data1 GPIOPinWrite(PD,P_3,P_3)
#define data0 GPIOPinWrite(PD,P_3,0)
extern void GPIO_INIT();
extern void delay(int t);
extern void dac_sendbite(uint16_t a);

#endif
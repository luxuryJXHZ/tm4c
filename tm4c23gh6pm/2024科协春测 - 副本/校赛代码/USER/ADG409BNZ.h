#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <lxy_uart.h>
#include <key.h>


#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"
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
#include "driverlib/pwm.h"

#include "uc1701.h"
#include "hw_uc1701.h"
#include "utils/uartstdio.h"

#ifndef ADG409BNZ_H
#define ADG409BNZ_H
#define ADG409BNZ_A0_1 	GPIOPinWrite(PF,P_1,P_1)
#define ADG409BNZ_A0_0 	GPIOPinWrite(PF,P_1,0)
#define ADG409BNZ_A1_1 	GPIOPinWrite(PD,P_0,P_0)
#define ADG409BNZ_A1_0 	GPIOPinWrite(PD,P_0,0)
#define ADG409BNZ1_A0_1 GPIOPinWrite(PD,P_3,P_3)
#define ADG409BNZ1_A0_0 GPIOPinWrite(PD,P_3,0) 
#define ADG409BNZ1_A1_1 GPIOPinWrite(PD,P_2,P_2)
#define ADG409BNZ1_A1_0 GPIOPinWrite(PD,P_2,0)
#endif
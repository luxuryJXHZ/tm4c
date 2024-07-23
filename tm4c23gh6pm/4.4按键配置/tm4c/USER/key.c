#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <key.h>


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
#include "utils/uartstdio.h"
void GPIO_INIT()
{
SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB); /* ʹ��ʱ�� */
    GPIODirModeSet( GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT); /* ����Ϊ���ģʽ */
    GPIOPadConfigSet( GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_STD); /* ///��һ������Ϊ 8mA����ת�����ʿ��Ƶ�������� */
    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);
	
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC); /* ʹ��ʱ�� */
    GPIODirModeSet( GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_DIR_MODE_OUT); /* ����Ϊ���ģʽ */
    GPIOPadConfigSet( GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_STD); /* ///��һ������Ϊ 8mA����ת�����ʿ��Ƶ�������� */
    GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); 

       GPIODirModeSet( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT); /* ����Ϊ���ģʽ */
    GPIOPadConfigSet( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_STD); /* ///��һ������Ϊ 8mA����ת�����ʿ��Ƶ�������� */
    GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5); 

	    GPIODirModeSet( GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT); /* ����Ϊ���ģʽ */
    GPIOPadConfigSet( GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_STRENGTH_8MA_SC,
    GPIO_PIN_TYPE_STD); /* ///��һ������Ϊ 8mA����ת�����ʿ��Ƶ�������� */
    GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6); 

    GPIOPinTypeGPIOInput( GPIO_PORTC_BASE, GPIO_PIN_7); /* ����GPIO_PIN Ϊ���� */
    GPIOPinTypeGPIOOutput( GPIO_PORTC_BASE,
    GPIO_PIN_2);
    GPIODirModeSet( GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet( GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
		
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
		GPIOPinTypeGPIOInput( GPIO_PORTD_BASE, GPIO_PIN_6); /* ����GPIO_PIN Ϊ���� */
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE,
    GPIO_PIN_6);
    GPIODirModeSet( GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet( GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
    
			GPIOPinTypeGPIOInput( GPIO_PORTD_BASE, GPIO_PIN_7); /* ����GPIO_PIN Ϊ���� */
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE,
    GPIO_PIN_7);
    GPIODirModeSet( GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet( GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_PIN_7);
		
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
			GPIOPinTypeGPIOInput( GPIO_PORTF_BASE, GPIO_PIN_4); /* ����GPIO_PIN Ϊ���� */
    GPIOPinTypeGPIOOutput( GPIO_PORTF_BASE,
    GPIO_PIN_4);
    GPIODirModeSet( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPinWrite( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

int KeyScan(void)
{
    int key = 17;
    /*
     * ���̼��ԭ�� ��ĳ����������͵�ƽ
     * ��0��
     */
    /* ȫ������͵�ƽ */
    keyout1_o0;
    keyout2_o0;
    keyout3_o0;
    keyout4_o0;
    if ((key_int_1 == 1) || (key_int_2 == 1) || (key_int_3 == 1)
            || (key_int_4 == 1))
    {
        return key;
    }

    keyout1_o0;
    keyout2_o1;
    keyout3_o1;
    keyout4_o1;
    if ((key_int_1 == 0) || (key_int_2 == 0) || (key_int_3 == 0)
            || (key_int_4 == 0))
    {
        if ( key_int_1 == 0)
        {
            key = 0;
        }
        else if ( key_int_2 == 0)
        {
            key = 4;
        }
        else if ( key_int_3 == 0)
        {
            key = 8;
        }
        else if ( key_int_4 == 0)
        {
            key = 12;
        }
    }

    /* ��1�� */
    keyout1_o1;
    keyout2_o0;
    keyout3_o1;
    keyout4_o1;
    if ((key_int_1 == 0) || (key_int_2 == 0) || (key_int_3 == 0)
            || (key_int_4 == 0))
    {
        if ( key_int_1 == 0)
        {
            key = 1;
        }
        else if ( key_int_2 == 0)
        {
            key = 5;
        }
        else if ( key_int_3 == 0)
        {
            key = 9;
        }
        else if ( key_int_4 == 0)
        {
            key = 13;
        }
    }
    /* ��2�� */
    keyout1_o1;
    keyout2_o1;
    keyout3_o0;
    keyout4_o1;
    if ((key_int_1 == 0) || (key_int_2 == 0) || (key_int_3 == 0)
            || (key_int_4 == 0))
    {
        if ( key_int_1 == 0)
        {
            key = 2;
        }
        else if ( key_int_2 == 0)
        {
            key = 6;
        }
        else if ( key_int_3 == 0)
        {
            key = 10;
        }
        else if ( key_int_4 == 0)
        {
            key = 14;
        }
    }
    /* ��3�� */
    keyout1_o1;
    keyout2_o1;
    keyout3_o1;
    keyout4_o0;
    if ((key_int_1 == 0) || (key_int_2 == 0) || (key_int_3 == 0)
            || (key_int_4 == 0))
    {
        if ( key_int_1 == 0)
        {
            key = 3;
        }
        else if ( key_int_2 == 0)
        {
            key = 7;
        }
        else if ( key_int_3 == 0)
        {
            key = 11;
        }
        else if ( key_int_4 == 0)
        {
            key = 15;
        }
    }

    /* ȫ������͵�ƽ */
    keyout1_o0;
    keyout2_o0;
    keyout3_o0;
    keyout4_o0;
    while ((key_int_1 == 0) || (key_int_2 == 0) || (key_int_3 == 0)
            || (key_int_4 == 0))
        ; /* �ȴ������ɿ� */

    return (key);
}


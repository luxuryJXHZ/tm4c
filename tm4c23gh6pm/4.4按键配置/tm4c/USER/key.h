#ifndef key_H
#define key_H
#include <stdint.h>
#define keyout1_o1  GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3 ) /* 让引脚输出高电平 */
#define keyout2_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4 ) /* 让引脚输出高电平 */
#define keyout3_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5 ) /* 让引脚输出高电平 */
#define keyout4_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_3 ) /* 让引脚输出高电平 */

#define keyout1_o0  GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_3, 0 )          /* 让引脚输出低电平 */
#define keyout2_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_4, 0 )          /* 让引脚输出低电平 */
#define keyout3_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, 0 )          /* 让引脚输出低电平 */
#define keyout4_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_6, 0 )          /* 让引脚输出低电平 */
/*
 * row 1234分别是  PP2 PN3 PN2 PD0 设置为in
 * col     分别是  PD1 PH3 PH2 PM3 设置为out
 */
#define key_int_1   GPIOPinRead( GPIO_PORTC_BASE, GPIO_PIN_7)              /* 读取引脚的电平是高还是低 */
#define key_int_2   GPIOPinRead( GPIO_PORTD_BASE, GPIO_PIN_6 )              /* 读取引脚的电平是高还是低 */
#define key_int_3   GPIOPinRead( GPIO_PORTD_BASE, GPIO_PIN_7 )              /* 读取引脚的电平是高还是低 */
#define key_int_4   GPIOPinRead( GPIO_PORTF_BASE, GPIO_PIN_4 )              /* 读取引脚的电平是高还是低 */

extern void GPIO_INIT();
int KeyScan(void);
#endif

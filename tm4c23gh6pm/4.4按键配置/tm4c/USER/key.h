#ifndef key_H
#define key_H
#include <stdint.h>
#define keyout1_o1  GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3 ) /* ����������ߵ�ƽ */
#define keyout2_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4 ) /* ����������ߵ�ƽ */
#define keyout3_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5 ) /* ����������ߵ�ƽ */
#define keyout4_o1  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_3 ) /* ����������ߵ�ƽ */

#define keyout1_o0  GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_3, 0 )          /* ����������͵�ƽ */
#define keyout2_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_4, 0 )          /* ����������͵�ƽ */
#define keyout3_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_5, 0 )          /* ����������͵�ƽ */
#define keyout4_o0  GPIOPinWrite( GPIO_PORTC_BASE, GPIO_PIN_6, 0 )          /* ����������͵�ƽ */
/*
 * row 1234�ֱ���  PP2 PN3 PN2 PD0 ����Ϊin
 * col     �ֱ���  PD1 PH3 PH2 PM3 ����Ϊout
 */
#define key_int_1   GPIOPinRead( GPIO_PORTC_BASE, GPIO_PIN_7)              /* ��ȡ���ŵĵ�ƽ�Ǹ߻��ǵ� */
#define key_int_2   GPIOPinRead( GPIO_PORTD_BASE, GPIO_PIN_6 )              /* ��ȡ���ŵĵ�ƽ�Ǹ߻��ǵ� */
#define key_int_3   GPIOPinRead( GPIO_PORTD_BASE, GPIO_PIN_7 )              /* ��ȡ���ŵĵ�ƽ�Ǹ߻��ǵ� */
#define key_int_4   GPIOPinRead( GPIO_PORTF_BASE, GPIO_PIN_4 )              /* ��ȡ���ŵĵ�ƽ�Ǹ߻��ǵ� */

extern void GPIO_INIT();
int KeyScan(void);
#endif

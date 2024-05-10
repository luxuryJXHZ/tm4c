#include <stdint.h>
#ifndef lxy_PWM_H
#define lxy_PWM_H

extern void PWM_init();
extern void PWM_duty(uint32_t ui32Base,uint32_t ui32PWMOut,uint32_t ui32PWMOutBits,uint32_t ui32Gen,float duty);



#endif
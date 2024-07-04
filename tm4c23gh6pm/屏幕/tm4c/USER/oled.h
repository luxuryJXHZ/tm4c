#ifndef OLED_H
#define OLED_H
#include <stdint.h>
#define  OLED_SCL_PIN     GPIO_PIN_3 //PF3
#define  OLED_SDA_PIN     GPIO_PIN_4 //PF4
#define  u8      uint8_t
#define  u32      uint32_t
#define OLED_width 128
#define OLED_height 64
#define page 8
#define  OLED_CMD       0
#define  OLED_DATA       1
#define  SCL0 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0)
#define  SCL1 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3)
#define  SDA0 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,0)
#define  SDA1 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_PIN_4)
#define  SDAr GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)
#define res1  GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2)
#define  res0 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0)
int I2C_RecvACK(void);
void I2C_SendACK(int ack);

void I2C_Start(void);
void I2C_Stop(void);
void I2C_waitack(void);
void I2C_SendByte(uint8_t dat);
void I2C_Init(void);
void OLED_WR_Byte(uint8_t dat,uint8_t mode);
void OLED_init(void);
void OLED_clear(void);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_address(uint8_t x, uint8_t y);
void OLEDShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);
void OLEDShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);
u32 OLED_Pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_Refresh(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
#endif


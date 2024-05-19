#include <stdbool.h>
#include "stdbool.h"
#include <stdint.h>
#include <stdio.h>
#include <start.h>
#include <lxy_ADC.h>
#include <lxy_PWM.h>
#include <ADG409BNZ.h>
#include <key.h>
#include <lxy_uart.h>
#include <math.h>


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
void up1();//用于向上翻
void down1();//用于向下翻
void enter1();//用于确定
void init();//初始化所有端口
void gpioinit();
void secernprintf(char *p,int x);//用于屏幕打印
void AC_1();//此函数用于测量量程为0.2v的直流电压
void AC_2();//此函数用于测量量程为2V的直流电压
void AC_3();//此函数用于测量量程为20V的直流电压
void DC_1();//此函数用于测量量程为0.2V的交流电压
void DC_2();//此函数用于测量量程为2V的交流电压
void DC_3();//此函数用于测量量程为20V的交流电压
void R_1();//此函数用于测量量程为200Ω的电阻
void R_2();//此函数用于测量量程为2kΩ的电阻
void R_3();//此函数用于测量量程为20kΩ的电阻
void R_4();
void squarewave();
void thd();
void pwm();
int i=0;
struct{
	int current;
	int up;
	int down;
	int enter;
} key_table[30]=
{
	{0,0,0,1,},
	//第一层
	{1,4,2,5},
	{2,1,3,8},
	{3,2,4,11},
	{4,3,1,15},
	
	{5,7,6,18},
	{6,5,7,19},
	{7,6,5,20},
	
	{8,10,9,21},
	{9,8,10,22},
	{10,9,8,23},
	
	{11,14,12,24},
	{12,11,13,25},
	{13,12,14,26},
	{14,13,11,27},
	
	{15,17,16,28},
	{16,15,17,29},
	{17,16,15,30}
	
	

	
};//菜单结构体定义
int main(void)
{SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);
	init ();
	key_INT();
	GPIOIntRegister(PD,up1);
	GPIOIntRegister(PF,down1);
	GPIOIntRegister(PA,enter1);
	key_enable();
	UC1701Init(60000);
	UART0_INT();
	gpioinit();
	ADG409BNZ_A0_0;
	ADG409BNZ_A1_0;
	while(1)
	{	
    switch (i)
			{case 0:UC1701Clear();UC1701CharDispaly(0,2,"start");break;
				case 1:UC1701Clear();UC1701CharDispaly(0,0,"AC<");
				UC1701CharDispaly(1,0,"DC");
				UC1701CharDispaly(2,0,"R");
				UC1701CharDispaly(3,0,"others");break;
				case 2:UC1701Clear();UC1701CharDispaly(0,0,"AC");
				UC1701CharDispaly(1,0,"DC<");
				UC1701CharDispaly(2,0,"R");
				UC1701CharDispaly(3,0,"others");break;
				case 3:UC1701Clear();UC1701CharDispaly(0,0,"AC");
				UC1701CharDispaly(1,0,"DC");
				UC1701CharDispaly(2,0,"R<");
				UC1701CharDispaly(3,0,"others");break;
				case 4:UC1701CharDispaly(0,0,"AC");
				UC1701CharDispaly(1,0,"DC");
				UC1701CharDispaly(2,0,"R");
				UC1701CharDispaly(3,0,"others<");break;
				case 5:UC1701Clear();UC1701CharDispaly(0,0,"0.2V<");
				UC1701CharDispaly(1,0,"2V");
				UC1701CharDispaly(2,0,"20V");break;
				case 6:UC1701Clear();UC1701CharDispaly(0,0,"0.2V");
				UC1701CharDispaly(1,0,"2V<");
				UC1701CharDispaly(2,0,"20V");break;
				case 7:UC1701Clear();UC1701CharDispaly(0,0,"0.2V");
				UC1701CharDispaly(1,0,"2V");
				UC1701CharDispaly(2,0,"20V<");break;
				case 8:UC1701Clear();UC1701CharDispaly(0,0,"0.2V<");
				UC1701CharDispaly(1,0,"2V");
				UC1701CharDispaly(2,0,"20V");break;
				case 9:UC1701Clear();UC1701CharDispaly(0,0,"0.2V");
				UC1701CharDispaly(1,0,"2V<");
				UC1701CharDispaly(2,0,"20V");break;
				case 10:UC1701Clear();UC1701CharDispaly(0,0,"0.2V");
				UC1701CharDispaly(1,0,"2V");
				UC1701CharDispaly(2,0,"20V<");break;
				case 11:UC1701Clear();UC1701CharDispaly(0,0,"200<");
				UC1701CharDispaly(1,0,"2k");
				UC1701CharDispaly(2,0,"20k");
					UC1701CharDispaly(3,0,"200k");break;
				case 12:UC1701Clear();UC1701CharDispaly(0,0,"200");
				UC1701CharDispaly(1,0,"2k<");
				UC1701CharDispaly(2,0,"20k");
					UC1701CharDispaly(3,0,"200k");break;
				case 13:UC1701Clear();UC1701CharDispaly(0,0,"200");
				UC1701CharDispaly(1,0,"2k");
				UC1701CharDispaly(2,0,"20k<");
				UC1701CharDispaly(3,0,"200k");break;
				case 14:UC1701Clear();UC1701CharDispaly(0,0,"200");
				UC1701CharDispaly(1,0,"2k");
				UC1701CharDispaly(2,0,"20k");
				UC1701CharDispaly(3,0,"200k<");break;
				case 15:UC1701Clear();UC1701CharDispaly(0,0,"fequence and duty<");
				UC1701CharDispaly(1,0,"thd");
				UC1701CharDispaly(2,0,"pwm");break;
					case 16:UC1701Clear();UC1701CharDispaly(0,0,"fequence and duty");
				UC1701CharDispaly(1,0,"thd<");
				UC1701CharDispaly(2,0,"pwm");break;
				case 17:UC1701Clear();UC1701CharDispaly(0,0,"fequence and duty<");
				UC1701CharDispaly(1,0,"thd");
				UC1701CharDispaly(2,0,"pwm<");break;
				case 18:AC_1();break;
				case 19:AC_2();break;
				case 20:AC_3();break;
				case 21:DC_1();break;
				case 22:DC_2();break;
				case 23:DC_3();break;
				case 24:R_1();break;
				case 25:R_2();break;
				case 26:R_3();break;
			
		}
				SysCtlDelay(SysCtlClockGet()/3000*100);
	}
}
void up1()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTD_BASE,true);
	if((status&GPIO_INT_PIN_7)==GPIO_INT_PIN_7)
{GPIOIntClear(GPIO_PORTD_BASE,status);
i=key_table[i].up;}
}
void down1()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTF_BASE,true);
	if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4)
{GPIOIntClear(GPIO_PORTF_BASE,status);
i=key_table[i].down;}
}
void enter1()
{uint32_t status;
	status=GPIOIntStatus(GPIO_PORTA_BASE,true);
	if((status&GPIO_INT_PIN_3)==GPIO_INT_PIN_3)
{GPIOIntClear(GPIO_PORTA_BASE,status);
i=key_table[i].enter;}}
void init()
{	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
}
void gpioinit()
{GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0);
		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3);
			GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2);
}
void secernprintf(char *str,int x)
{int zheng;
	int xiao;
	zheng=x/1000;
	xiao=x-zheng*1000;
	sprintf(str,"%d.%03d",zheng,xiao);
}
	
void AC_1()
	{ ADG409BNZ_A0_1;
		ADG409BNZ_A1_0;
		ADG409BNZ1_A0_1;
		ADG409BNZ1_A1_0;
		uint32_t adepeovalue=0; 
		int k;
		int sum=0;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
		for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
		int average=sum/100;
//		if(average>200)
//		i=i+1;
//		else
		secernprintf(str,average);
			UC1701Clear();
		UC1701CharDispaly(0,0,"AIN1:");
		UC1701CharDispaly(1,0,str);
	}
	void AC_2()
	{
		ADG409BNZ_A0_0;
		ADG409BNZ_A1_0;
		uint32_t adepeovalue=0; 
		int sum=0;
		int k;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
		for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
		int avaeage=sum/100;
//		if(avaeage>2000)
//		i=i+1;
//		else if(avaeage<200)
//			i=i-1;
//		else
   	secernprintf(str,avaeage);
		UC1701Clear();
		UC1701CharDispaly(0,0,"AIN2:");
		UC1701CharDispaly(1,0,str);
		
	}
		void AC_3()
	{
		ADG409BNZ_A0_0;
		ADG409BNZ_A1_0;
		ADG409BNZ1_A0_0;
		ADG409BNZ1_A1_1;
		uint32_t adepeovalue=0; 
		int sum=0;
		int k;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
		TimerEnable (TIMER1_BASE,TIMER_B );
		for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
		int avaeage=sum/100;

//		if(avaeage>20000)
//		{SysCtlPeripheralPowerOff(ADC1_BASE);}
//		else if(avaeage<2000) i=i-1;
//		else
	  secernprintf(str,avaeage);
		UC1701Clear();
		UC1701CharDispaly(0,0,"AIN3:");
		UC1701CharDispaly(1,0,str);
		
	}
void DC_1()
{		uint32_t adepeovalue; 
		double  sum=0;
		int k;
		int DC_V[256];
		char str[20];
		char str1[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
		TimerEnable (TIMER1_BASE,TIMER_B );
		for(k=0;k<256;k++){
    int dam=0;
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		dam=adepeovalue*3300/4096;
		if(dam>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
		sum=sum+dam*dam;
		}
		sum=sqrt(sum/256);
//		if(sum>200)
//		{i=i+1;
//		}
		secernprintf(str,sum);
		secernprintf(str1,sum/1.414);
		
		UC1701Clear();
		UC1701CharDispaly(0,0,"ampliude1");
		UC1701CharDispaly(1,0,str);
		UC1701CharDispaly(2,0,"virtual value1");
		UC1701CharDispaly(3,0,str1);
}
    

void DC_2()
{uint32_t adepeovalue=0; 
   double  sum=0;
	int k;
	int DC_V[256];
		char str[20];
	char str1[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
			TimerEnable (TIMER1_BASE,TIMER_B );
	for(k=0;k<256;k++){
      int dam=0;
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		dam=adepeovalue*3300/4096;
		if(dam>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
		sum=sum+dam*dam;
		}
		sum=sqrt(sum/256);
//	if(sum<200)
//		i=i-1;
//	if(sum>20000)
//		i=i+1;
	secernprintf(str,sum);
		secernprintf(str1,sum/1.414);
		
			UC1701Clear();
		UC1701CharDispaly(0,0,"ampliude 2");
		UC1701CharDispaly(1,0,str);
		UC1701CharDispaly(2,0,"virtual value 2");
		UC1701CharDispaly(3,0,str1);}
void DC_3()
{uint32_t adepeovalue; 
	double  sum=0;
	int k;
	int DC_V[256];
	char str[20];
	char str1[20];
	ADC_init_SS3();
	ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
	TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
	TimerEnable (TIMER1_BASE,TIMER_B );
	for(k=0;k<256;k++){
      int dam=0;
			TimerControlTrigger(TIMER1_BASE,TIMER_B,true);
			ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
			dam=adepeovalue*3300/4096;
			if(dam>3300) SysCtlPeripheralPowerOff(ADC1_BASE);
		 sum=sum+dam*dam;
		}
	secernprintf(str,sum);
		secernprintf(str1,sum/1.414);
		if(sum<2000)
		{i=i-1;
		}
			UC1701Clear();
		UC1701CharDispaly(0,0,"ampliude3");
		UC1701CharDispaly(1,0,str);
		UC1701CharDispaly(2,0,"virtual value3");
		UC1701CharDispaly(3,0,str1);}
void R_1()
{uint32_t adepeovalue=0; 
		int sum=0;
	int  k;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
		TimerEnable (TIMER1_BASE,TIMER_B );
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
	  secernprintf(str,sum);
		UC1701Clear();
		UC1701CharDispaly(0,0,"R_1:");
		UC1701CharDispaly(1,0,str);}
void R_2()
{uint32_t adepeovalue=0; 
		int sum=0;
	int  k;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
		TimerEnable (TIMER1_BASE,TIMER_B );
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
	  secernprintf(str,sum);
		UC1701Clear();
		UC1701CharDispaly(0,0,"R_2");
		UC1701CharDispaly(1,0,str);}
void R_3()
{uint32_t adepeovalue=0; 
		int sum=0;
	int  k;
		char str[20];
		ADC_init_SS3();
		ADC_SS3_SET(ADC_TRIGGER_TIMER,ADC_CTL_CH1);
		TimerConfigure(TIMER1_BASE,TIMER_CFG_B_PERIODIC|TIMER_CFG_SPLIT_PAIR);
		TimerEnable (TIMER1_BASE,TIMER_B );
for(k=0;k<100;k++){
		TimerControlTrigger(TIMER1_BASE,TIMER_B,true);	
		ADCSequenceDataGet(ADC1_BASE,3,&adepeovalue);
		sum=sum+adepeovalue*3300/4096;}
		sum=adepeovalue*3300/4096;
	  secernprintf(str,sum);
		UC1701Clear();
		UC1701CharDispaly(0,0,"R_3:");
		UC1701CharDispaly(1,0,str);}

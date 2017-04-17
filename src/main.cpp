#include "stm32f30x_conf.h"
#include "OLED_DISPLAY.hpp"
#include "core_cm4.h"

OLED_DISPLAY oleddisp(0);
volatile unsigned int addr;
static unsigned int systick=0;
unsigned short test;
volatile static int t2;

int main(void)
{	
	SysTick_Config(64000000/10000); 
	oleddisp.oled_dev.init();
	int i;
	//for(i=0;i<64*96;i++)
	//{
	//  oleddisp.setPoint(i%96,i/96,RGB888_TO_RGB565U16(i/2/96*8,0,0));
	//}

	while(1)
	{
		int cnt;
		cnt=100;
		for(i=0;i<64*96;i++)
		{
			oleddisp.setPoint(i%96,i/96,RGB888_TO_RGB565U16(i/2/96*8,0,0));
		}
		while(cnt--)
		{
			volatile int t0=systick;
			oleddisp.flushAll();
			volatile int t1=systick;
			t2=t1-t0;
		}
		
		cnt=100;
		for(i=0;i<64*96;i++)
		{
			oleddisp.setPoint(i%96,i/96,RGB888_TO_RGB565U16(0,i/96*4,0));
		}
		while(cnt--)
		{
			volatile int t0=systick;
			oleddisp.flushAll();
			volatile int t1=systick;
			t2=t1-t0;
		}
		
		cnt=100;
		for(i=0;i<64*96;i++)
		{
			oleddisp.setPoint(i%96,i/96,RGB888_TO_RGB565U16(0,0,i/2/96*8));
		}
		while(cnt--)
		{
			volatile int t0=systick;
			oleddisp.flushAll();
			volatile int t1=systick;
			t2=t1-t0;
		}
		
	}//end of while(1)
	
}

extern "C" void SysTick_Handler(void)
{
	systick++;
}




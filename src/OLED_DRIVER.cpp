#include "OLED_DRIVER.hpp"
#pragma push 
#pragma	Otime	O3
inline void OLED_DRIVER_HW::SDO_H()
{
	GPIOA->BSRR = GPIO_Pin_6;
}

inline void OLED_DRIVER_HW::SDO_L()
{
	GPIOA->BRR = GPIO_Pin_6;
}

inline void OLED_DRIVER_HW::SCLK_H()
{
	GPIOA->BSRR = GPIO_Pin_7;
}

inline void OLED_DRIVER_HW::SCLK_L()
{
	GPIOA->BRR = GPIO_Pin_7;
}

inline void OLED_DRIVER_HW::CS_ENABLE()
{
	GPIOB->BRR = GPIO_Pin_6;
}

inline void OLED_DRIVER_HW::CS_DISABLE()
{
	GPIOB->BSRR = GPIO_Pin_6;
}

void OLED_DRIVER_HW::DC_H()
{
	GPIOC->BSRR = GPIO_Pin_7;
}

inline void OLED_DRIVER_HW::DC_L()
{
	GPIOC->BRR = GPIO_Pin_7;
}	

inline void OLED_DRIVER_HW::RESET_H()
{
	GPIOA->BSRR = GPIO_Pin_9;
}

inline void OLED_DRIVER_HW::RESET_L()
{
	GPIOA->BRR = GPIO_Pin_9;
}

inline void OLED_DRIVER_HW::DELAY_US(unsigned int us)
{
	//it is not correct!!!! 
	us*=500;
	while(us--);
}

inline void OLED_DRIVER_HW::spiWrite(unsigned char wData)
{
	int i;
	for(i=7;i>=0;i--)
	{
		SCLK_L();
		if(	wData&(1<<i) ) 
			SDO_H();
		else
			SDO_L();
		SCLK_H();
	}
}

void OLED_DRIVER_HW::writeCmd(unsigned char cmd)
{
	DC_L();
	spiWrite(cmd);
}

void OLED_DRIVER_HW::writeCmd(unsigned char cmd,unsigned char data1)
{
	DC_L();
	spiWrite(cmd);
	spiWrite(data1);
}

void OLED_DRIVER_HW::writeCmd(unsigned char cmd,unsigned char data1,unsigned char data2)
{
	DC_L();
	spiWrite(cmd);
	spiWrite(data1);
	spiWrite(data2);
}

void OLED_DRIVER_HW::writeData(unsigned char data)
{
	//DC_H();
	spiWrite(data);
}

void OLED_DRIVER_HW::hardwareReset()
{
	CS_DISABLE();
	DC_H();
	SCLK_H();
	SDO_H();
	RESET_L();
	
	DELAY_US(10000);
	RESET_H();
	CS_ENABLE();
	DELAY_US(10000);
}

void OLED_DRIVER_HW::initRegs()
{	
	writeCmd( DISPLAY_OFF );  	// 
	writeCmd( SET_CONTRAST_A, 0xff);
	writeCmd( SET_CONTRAST_B, 0xff);
	writeCmd( SET_CONTRAST_C, 0xff);
	writeCmd( MASTER_CURRENT_CONTROL, 0x06);
	writeCmd( SET_PRECHARGE_SPEED_A, 0x64);
	writeCmd( SET_PRECHARGE_SPEED_B, 0x78);
	writeCmd( SET_PRECHARGE_SPEED_C, 0x64);
	writeCmd( SET_REMAP, 0x72);
	writeCmd( SET_DISPLAY_START_LINE, 0x0);
	writeCmd( SET_DISPLAY_OFFSET, 0x0);
	writeCmd( NORMAL_DISPLAY);
	writeCmd( SET_MULTIPLEX_RATIO, 0x3f);
	writeCmd( SET_MASTER_CONFIGURE, 0x8E);
	writeCmd( PHASE_PERIOD_ADJUSTMENT, 0x31);
	writeCmd( DISPLAY_CLOCK_DIV, 0xF0);
	writeCmd( SET_PRECHARGE_VOLTAGE, 0x3A);
	writeCmd( SET_V_VOLTAGE, 0x3E);
	writeCmd( DEACTIVE_SCROLLING);
	writeCmd( NORMAL_BRIGHTNESS_DISPLAY_ON);
}

void OLED_DRIVER_HW::initGpio()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6 | 
									GPIO_Pin_7 | 
									GPIO_Pin_9 ; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void OLED_DRIVER_HW::init()
{
	initGpio();
	hardwareReset();
	initRegs();
}

void OLED_DRIVER_HW::setPostion(unsigned char x1,unsigned char y1)
{
	if ((x1 >= WIDTH) || (y1 >= HEIGHT))
		return;
	writeCmd( SET_COLUMN_ADDRESS, x1, WIDTH-1);
	writeCmd( SET_ROW_ADDRESS, y1, HEIGHT-1 );
	return;
}

void OLED_DRIVER_HW::setPostion(unsigned char x1,unsigned char y1,unsigned char x2, unsigned char y2)
{
	if ((x1 >= WIDTH) || (y1 >= HEIGHT))
		return;
	if ((x2 >= WIDTH) || (y2 >= HEIGHT))
		return;
	writeCmd( SET_COLUMN_ADDRESS, x1, x2);
	writeCmd( SET_ROW_ADDRESS, y1, y2 );
	return;
}

void OLED_DRIVER_HW::setColor(unsigned short color)
{
	writeData( color >> 8 );
	writeData( color & 0xff );
	return;
}

void OLED_DRIVER_HW::setColor(unsigned char x,unsigned char y,unsigned short color)
{
	//move to x,y
	//not finish here
	writeData( color >> 8 );
	writeData( color & 0xff );
	return;
}

#pragma pop




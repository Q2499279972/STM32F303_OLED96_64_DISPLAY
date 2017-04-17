#ifndef _OLED_DRIVER_HPP_
#define _OLED_DRIVER_HPP_

#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

#define DRAW_LINE                       0x21
#define DRAW_RECTANGLE                  0x22
#define COPY_WINDOW                     0x23
#define DIM_WINDOW                      0x24
#define CLEAR_WINDOW                    0x25
#define FILL_WINDOW                     0x26
#define DISABLE_FILL                    0x00
#define ENABLE_FILL                     0x01
#define CONTINUOUS_SCROLLING_SETUP      0x27
#define DEACTIVE_SCROLLING              0x2E
#define ACTIVE_SCROLLING                0x2F

#define SET_COLUMN_ADDRESS              0x15
#define SET_ROW_ADDRESS                 0x75
#define SET_CONTRAST_A                  0x81
#define SET_CONTRAST_B                  0x82
#define SET_CONTRAST_C                  0x83
#define MASTER_CURRENT_CONTROL          0x87
#define SET_PRECHARGE_SPEED_A           0x8A
#define SET_PRECHARGE_SPEED_B           0x8B
#define SET_PRECHARGE_SPEED_C           0x8C
#define SET_REMAP                       0xA0
#define SET_DISPLAY_START_LINE          0xA1
#define SET_DISPLAY_OFFSET              0xA2
#define NORMAL_DISPLAY                  0xA4
#define ENTIRE_DISPLAY_ON               0xA5
#define ENTIRE_DISPLAY_OFF              0xA6
#define INVERSE_DISPLAY                 0xA7
#define SET_MULTIPLEX_RATIO             0xA8
#define DIM_MODE_SETTING                0xAB
#define SET_MASTER_CONFIGURE            0xAD
#define DIM_MODE_DISPLAY_ON             0xAC
#define DISPLAY_OFF                     0xAE
#define NORMAL_BRIGHTNESS_DISPLAY_ON    0xAF
#define POWER_SAVE_MODE                 0xB0
#define PHASE_PERIOD_ADJUSTMENT         0xB1
#define DISPLAY_CLOCK_DIV               0xB3
#define SET_GRAy_SCALE_TABLE            0xB8
#define ENABLE_LINEAR_GRAY_SCALE_TABLE  0xB9
#define SET_PRECHARGE_VOLTAGE           0xBB
#define SET_V_VOLTAGE                   0xBE

#pragma push 
#pragma	Otime	O3
class OLED_DRIVER_HW
{
public:
	static const int WIDTH=96;
	static const int HEIGHT=64;
	inline void SDO_H();
	inline void SDO_L();
	inline void SCLK_H();
	inline void SCLK_L();
	inline void CS_ENABLE();
	inline void CS_DISABLE();
	//inline char SDI(){;return 0;}
	void DC_H();
	inline void DC_L();
	inline void RESET_H();
	inline void RESET_L();
	inline void DELAY_US(unsigned int us);
	inline void spiWrite(unsigned char wData);
	void writeCmd(unsigned char cmd);
	void writeCmd(unsigned char cmd,unsigned char data1);
	void writeCmd(unsigned char cmd,unsigned char data1,unsigned char data2);
	void writeData(unsigned char data);
	void hardwareReset();
	void initRegs();	
	void initGpio();
	void init();
	void setPostion(unsigned char x1,unsigned char y1);
	void setPostion(unsigned char x1,unsigned char y1,unsigned char x2, unsigned char y2);
	void setColor(unsigned short color);	
	void setColor(unsigned char x,unsigned char y,unsigned short color);
};
#pragma pop	
#endif

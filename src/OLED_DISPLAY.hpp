#ifndef _OLED_DISPLAY_HPP_
#define _OLED_DISPLAY_HPP_
#include "OLED_DRIVER.hpp"

#warning []
#define RGB888_TO_RGB565U16(r,g,b) ( ( unsigned short )( ((r>>3)<<11) | ((g>>2)<<5) | (b>>3) ) )

class OLED_DISPLAY
{
public:
	static const unsigned char m_width=96;
	static const unsigned char m_height=64;
	unsigned short m_displayBuffer[m_width*m_height];
  
	unsigned char m_clearColorRed;
	unsigned char m_clearColorGreean;
	unsigned char m_clearColorBlue;

	OLED_DRIVER_HW oled_dev;
	
	OLED_DISPLAY(unsigned char r=0,unsigned char g=0,unsigned char b=0);
	void setPoint(unsigned char x,unsigned char y,unsigned short color);
	void flushAll();
};

#endif

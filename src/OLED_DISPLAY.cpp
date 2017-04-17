#include "OLED_DISPLAY.HPP"

OLED_DISPLAY::OLED_DISPLAY(unsigned char r,unsigned char g,unsigned char b)
{
	m_clearColorRed=r;
	m_clearColorGreean=g;
	m_clearColorBlue=b;
	int i;
	unsigned short color=RGB888_TO_RGB565U16(r,g,b);
	for(i=0;i<m_width*m_height;i++)
	{
		m_displayBuffer[i++]=color;
	}
}

void OLED_DISPLAY::setPoint(unsigned char x,unsigned char y,unsigned short color)
{
	m_displayBuffer[x+y*m_width]=color;
}

void OLED_DISPLAY::flushAll()
{
	int i;
	oled_dev.setPostion(0,0,95,63);
	oled_dev.DC_H();
	for(i=0;i<m_width*m_height;i++)
	{
		oled_dev.setColor(m_displayBuffer[i]);
	}
}



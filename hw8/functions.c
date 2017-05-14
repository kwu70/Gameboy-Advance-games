//Kenny Wu

#include "mylib.h"

u16 *videoBuffer = (u16*)0x6000000;

void setPixel(int r, int c, u16 color)
{
	videoBuffer[OFFSET(r, c)] = color;
}

void drawRect(int r, int c, int height, int width, u16 color)
{
	for(int row = 1; row <= height; row++)
	{
		for(int col = 1; col <= width; col++)
		{
			setPixel(r+row, c+col, color);
		}
	}
}

void drawHollowRect(int r, int c, int height, int width, u16 color)
{
	for(int row = 1; row <= height; row++)
	{
		for(int col = 1; col <= width; col++)
		{
			if((row == 1) || (row == height) || (col == 1) || (col == width))
				setPixel(r+row, c+col, color);
		}
	}
}

void delay(int n)
{
	volatile int t;
	for(int i = 0; i < (n*5000); i++)
	{
		t += 1;
	}
}

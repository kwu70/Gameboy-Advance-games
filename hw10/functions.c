//Kenny Wu

#include "mylib.h"

u16 *videoBuffer = (u16*)0x6000000;

void setPixel(int r, int c, u16 color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void setPixel4(int row, int col, u8 index)
{
	int whichPixel = OFFSET(row, col, 240);
	int whichShort = whichPixel/2;
	
	if(col & 1)
	{
		//column is odd, we change left byte
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
	}
	else
	{
		//column is even, we change right byte
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | (index);
	}
}

void drawRect(int row, int col, int height, int width, u16 color)
{
    for(int r = 0; r < height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET((row+r), col, 240)];
        DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
        
    }
}
/*
void drawHollowRect(int row, int col, int height, int width, u16 color)
{
	for(int r = 0; r < height; row++)
	{
		if((r == 0) || (r == height-1))
		{
			DMA[3].src = &color;
        	DMA[3].dst = &videoBuffer[OFFSET((row+r), col, 240)];
       		DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
		}

		for(int c = 0; c < width; c++)
		{
			if((c == 0) || (c == width-1))
				setPixel(row+r, col+c, color);
		}
	}
}
*/

void drawRect4(int row, int col, int height, int width, u8 index)
{
	//we used volatile to store the color
	volatile u16 color = (index << 8) | index;

	for(int r = 0; r < height; r++)
	{
		DMA[3].src = &color; 
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)/2];
		DMA[3].cnt = (width/2) | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
	}
}

void drawQuad4Tri(int row, int col, int height, int width, u16 color)
{
	for(int m = 0; m < height; m++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET((row+m), (col+m), 240)];
        DMA[3].cnt = (width-m) | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
        
    }
}

void drawQuad2Tri(int row, int col, int height, int width, u16 color)
{
	for(int n = 0; n < height; n++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET((row+n), (col+width-n-1), 240)];
        DMA[3].cnt = (n+1) | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
        
    }
}

void drawImage3(int row, int col, int height, int width, const u16 *image)
{
	for(int i = 0; i < height; i++)
	{
		//DMA[3].src = image;
		DMA[3].src = image + (i*width);
		//DMA[3].src = image + OFFSET((row+i), col, 240);
		//note:offset is the location in memory to be drawn
		DMA[3].dst = videoBuffer + OFFSET((row+i), col, 240);
		DMA[3].cnt = width | DMA_ON;
	}
}

void fillScreen(u16 color)
{	
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;	
}

void fillScreen4(u8 index)
{
	volatile unsigned short color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_ON;
}

/*
void drawFullScreen(const u16 *bitmap[])
{	
	DMA[3].src = bitmap;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = DMA_ON | 38400;	

}
*/

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void flipPage()
{
	if(REG_DISPCNT & BUFFER1FLAG)
	{
		//we are displaying buffer 1
		videoBuffer = BUFFER1;
		REG_DISPCNT = REG_DISPCNT & ~BUFFER1FLAG;
	}
	else
	{
		//we are displaying buffer 0
		videoBuffer = BUFFER0;
		REG_DISPCNT = REG_DISPCNT | BUFFER1FLAG;	
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

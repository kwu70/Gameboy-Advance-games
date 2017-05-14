//Kenny Wu

#include "mylib.h"

u16 *videoBuffer = (u16*)0x6000000;

void setPixel(int r, int c, u16 color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
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
		DMA[3].src = image + (i*width);
		//DMA[3].src = image + OFFSET((row+i), col, 240);
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


/*
void drawFullScreen(const unsigned short bitmap[])
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

void delay(int n)
{
	volatile int t;
	for(int i = 0; i < (n*5000); i++)
	{
		t += 1;
	}
}

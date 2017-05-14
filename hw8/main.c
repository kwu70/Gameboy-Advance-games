//Kenny Wu

#include <stdlib.h>
#include "mylib.h"

int *KEYS = (int*)0x04000130;

int main()
{
	int r1, r2, r3;
	int move = 0;
	int up = 0, down = 0,right = 0, left = 0;

	REG_DISPCNT = BG2_EN | MODE_3;

	//hill	
	drawRect(120, 10, 25, 80, RGB(0, 15, 0));

	//wheels
	drawHollowRect(110, 30, 9, 30, RGB(10, 4, 0));
	drawHollowRect(110, 40, 9, 10, RGB(10, 4, 0));

	//tank body
	drawRect(100, 20, 10, 50, RGB(15, 15, 15));

	//tank top
	drawRect(89, 30, 10, 30, RGB(23, 23, 23));

	//tank cannon
	drawRect(92, 61, 4, 20, RGB(15, 31, 15));

	while(1)
	{
		//generate random colors
		r1 = rand() % 32;
		r2 = rand() % 32;
		r3 = rand() % 32;

		if(!(*KEYS & KEY_UP))
		{
			up -= 5;
			drawHollowRect((72 + up), 145, 10, 10, RGB(r1, r2, r3));
		}

		if(!(*KEYS & KEY_DOWN))
		{
			down += 5;
			drawHollowRect((103 + down), 145, 10, 10, RGB(r1, r2, r3));
		}

		if(!(*KEYS & KEY_RIGHT))
		{
			right += 5;
			drawHollowRect(87, (161 + right), 10, 10, RGB(r1, r2, r3));
		}

		if(!(*KEYS & KEY_LEFT))
		{
			if(left > -45)
			{
				left -= 5;
				drawHollowRect(87, (129 + left), 10, 10, RGB(r1, r2, r3));
			}
		}

		for(move = 0; move < 62; move++)		
		{
			drawRect(91, (move + 82), 4, 4, WHITE);
			delay(1);
			drawRect(91, (move + 82), 4, 4, BLACK);
		}
		
		//explosion
		drawHollowRect(73, 160, 10, 10, RGB(r1, r2, r3));
		drawHollowRect(73, 130, 10, 10, RGB(r1, r2, r3));
		drawRect(85, 143, 15, 15, RGB(r1, r2, r3));
		drawHollowRect(102, 160, 10, 10, RGB(r1, r2, r3));
		drawHollowRect(102, 130, 10, 10, RGB(r1, r2, r3));
	}

	return 0;
}



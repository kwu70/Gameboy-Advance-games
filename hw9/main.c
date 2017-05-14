//Kenny Wu

#include <stdio.h>
#include "mylib.h"
#include "text.h"
#include "Start.h"
#include "Win.h"
#include "GameOver.h"
#include "ship.h"
#include "asteroid.h"
#include "explosion.h"

enum {START, GAME, WIN, LOSE, RESET};

void start();
void win();
void lose();
int game();

int main()
{
	int condition;
	int state = START;
	REG_DISPCNT = MODE_3 | BG2_EN;
	
	while(1)
	{
		switch(state)
		{
		case START:
			start();
			state = GAME;
			break;
		case GAME:
			condition = game();
			if(condition == WIN)
				state = WIN;
			else if(condition == LOSE)
				state = LOSE;
			else if(condition == RESET)
				state = RESET;
			break;
		case WIN:
			win();
			state = GAME;
			break;
		case LOSE:
			lose();
			state = GAME;
			break;
		case RESET:
			state = START;
			break;
		}
	}
}	

void start()
{
	drawImage3(0, 0, 159, 239, Start);
	while(!KEY_DOWN_NOW(KEY_START));	//wait until start is pressed
}

void win()
{
	drawImage3(0, 0, 159, 239, Win);
	while(!KEY_DOWN_NOW(KEY_START));	//wait until start is pressed
}

void lose()
{
	drawImage3(0, 0, 159, 239, GameOver);
	while(!KEY_DOWN_NOW(KEY_START));	//wait until start is pressed
}

int game()
{	
	int state = GAME;
	char buffer[41];
	int rocket = 3;
	int row = 15;
	int col = 40;
	int m = 0;
	u16 bgcolor = BLACK;
	fillScreen(bgcolor);

	//draw background image
	drawRect(80, 0, 10, 175, GRAY);
	drawQuad4Tri(15, 195, 45, 45, SILVER);
	drawQuad2Tri(115, 195, 45, 45, SILVER);
	
	//draw asteroid
	drawImage3(115, 15, 19, 20, asteroid);

	while(state == GAME)
	{	
		waitForVblank();

		//print how many rocket is left
		sprintf(buffer, "Rocket: %d", rocket);
		drawRect(5, 98, 8, 24, BLACK);
		drawString(5, 55, buffer, RED);

		//move space ship up
		if((KEY_DOWN_NOW(KEY_UP))&&(row > 15)&&(row <= 60))
		{
			m--;
			row--;
		}
		//move space ship down
		if((KEY_DOWN_NOW(KEY_DOWN))&&(row >= 15)&&(row < 60))
		{
			m++;
			row++;
		}
		//reset game
		if(KEY_DOWN_NOW(KEY_SELECT))
		{
			state = RESET;
			return state;
		}

		//draw the space ship
		drawImage3(6+m, 10, 24, 30, ship);

		if(KEY_DOWN_NOW(KEY_A))
		{
			rocket--;
			sprintf(buffer, "Rocket: %d", rocket);
			drawRect(5, 98, 8, 24, BLACK);
			drawString(5, 55, buffer, RED);

			//move the rocket
			while(((col <= 235) && (col > 32)) && (row <= 155) )
			{
				if((col < (190+m)) && (row <= (15+m)))
				{
					col++;
				}
				else if(row < (155-m))
				{
					row++;
				}
				else if(col > 32)
				{
					col--;
				}

				//draw the rocket
				drawRect(row, col, 5, 5, BLUE);
				delay(1);		
				drawRect(row, col, 5, 5, BLACK);

				//condition for winning
				if(((row >= 115)&&(row <= 132))&&(col == 32))
				{	
					drawImage3(118, 15, 30, 27, explosion);
					delay(10);
					state = WIN;
				}
				else if(rocket == 0)
				{
					state = LOSE;
				}
			}
			//remove after image of space ship
			drawRect(6+m, 10, 24, 30, BLACK);
			//reset for next rocket to be fired
			row = 15;
			col = 40;
			m = 0;
		}
	}

	return state;
}

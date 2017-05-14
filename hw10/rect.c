//Kenny Wu

#include <stdlib.h>
#include <debugging.h>
#include "list.h"
#include "mylib.h"

typedef struct
{
	int r; // or y
	int c; // or x
	int dr;
	int dc;
	int height;
	int width;
	u8 color;
} Rectangle;

typedef struct
{
	int r;
	int c;
	int height;
	int width;
	u8 color;
} cursor;

void clear(void);
void update(void);
void draw(void);

/* Initialize any global variables here */

/* Note you will have to define additional functions to implement the functionality in the assignment*/

//void free_rect(void* data, list_op free_func);
void remove(void* data);
int remove_rand(const void* data);
void bounce(void* data);
Rectangle *obj(int row, int col);

enum {REDIDX, GREENIDX, BLUEIDX, CYANIDX, MAGENTAIDX, YELLOWIDX, WHITEIDX, SILVERIDX, BLACKIDX};

list *llist;
int randNum;
int counter = 0;
//for seeding the random number
int dels[] = {-3, -2, -1, 1, 2, 3};

cursor curs = {80, 120, 5, 5, BLUEIDX};

Rectangle *obj(int row, int col)
{
	Rectangle *newRect = malloc(sizeof(Rectangle));

	newRect->r = row;
	newRect->c = col;
	newRect->height = curs.height;
	newRect->width = curs.width;
	newRect->dr = dels[rand()%6];
	newRect->dc = dels[rand()%6];
	newRect->color = rand()%8;

	return newRect;
}

int main(void)
{
	/* SET UP REG_DISPCNT */
	/* INITIALIZE OR SET UP ANY VARIABLES YOU WANT */
	REG_DISPCNT = MODE_4 | BG2_EN;
	llist = create_list();	

	//store the color in the PALETTE to be used
	u16 colors[] = {RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, SILVER, BLACK};

	for(int i = 0; i < 9; i++)
	{
		PALETTE[i] = colors[i];
	}
	
	while(1)
	{
		/* You shouldn't need to change this part implement the game functionality in the three functions I have defined below */
		waitForVblank();
		clear();
		update();
		draw();
	}
}

/* You should clear any objects drawn in the previous frame here */
void clear(void)
{
	fillScreen4(BLACKIDX);
}

/* You should handle any key input in this function and update the game state */
void update(void)
{
	if(KEY_DOWN_NOW(BUTTON_UP))
	{
		if(curs.r > 0)
			curs.r--;
	}
	if(KEY_DOWN_NOW(BUTTON_DOWN))
	{
		if(curs.r < (159-(curs.width)))
			curs.r++;
	}

	if(KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		if(curs.c < (239-(curs.height)))
			curs.c++;
	}

	if(KEY_DOWN_NOW(BUTTON_LEFT))
	{
		if(curs.c > 0)
			curs.c--;
	}
	
	if(KEY_DOWN_NOW(BUTTON_A))
	{
		while(KEY_DOWN_NOW(BUTTON_A));
		push_front(llist, obj(curs.r, curs.c));
		//counter++;
	}

	if(KEY_DOWN_NOW(BUTTON_B))
	{
		while(KEY_DOWN_NOW(BUTTON_B));
		//counter--;
		counter = 0;
		randNum = rand()%(size(llist));
		remove_if(llist, remove_rand, remove);
	}

	if(KEY_DOWN_NOW(BUTTON_START))
	{
		while(KEY_DOWN_NOW(BUTTON_A));
		empty_list(llist, remove);
	}
}

/* You should draw all of your objects here */
void draw(void)
{
	drawRect4(curs.r, curs.c, curs.height, curs.width, curs.color);
	traverse(llist, bounce);
}

void bounce(void* data)
{
	((Rectangle*)data)->r =  ((Rectangle*)data)->r + ((Rectangle*)data)->dr;
	((Rectangle*)data)->c =  ((Rectangle*)data)->c + ((Rectangle*)data)->dc;
	
	if(((Rectangle*)data)->r < 0)
	{
		((Rectangle*)data)->r = 0;
		((Rectangle*)data)->dr = -(((Rectangle*)data)->dr);
	}
	
	if(((Rectangle*)data)->c < 0)
	{
		((Rectangle*)data)->c = 0;
		((Rectangle*)data)->dc = -(((Rectangle*)data)->dc);
	}

	if(((Rectangle*)data)->r > (159-(curs.height)))
	{
		((Rectangle*)data)->r = 159-(curs.height);
		((Rectangle*)data)->dr = -(((Rectangle*)data)->dr);
	}

	if(((Rectangle*)data)->c > (239-(curs.width)))
	{
		((Rectangle*)data)->c = 239-(curs.width);
		((Rectangle*)data)->dc = -(((Rectangle*)data)->dc);
	}

	drawRect4(((Rectangle*)data)->r, ((Rectangle*)data)->c,
	((Rectangle*)data)->height, ((Rectangle*)data)->width,
	((Rectangle*)data)->color );
}

int remove_rand(const void* data)
{
	if(counter == randNum)
	{
		return 1;
	}

	counter++;
	return 0;
}

void remove(void* data)
{
	free(data);
}


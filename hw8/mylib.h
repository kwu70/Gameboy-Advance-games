//Kenny Wu

typedef unsigned short u16;
#define REG_DISPCNT *(u16*) 0x4000000
#define BG2_EN (1 << 10)
#define MODE_3 3
#define RGB(r,g,b) ((r) | ((g) << 5) | ((b) << 10))
#define OFFSET(r,c) ((r * 240) + (c))

#define WHITE RGB(31,31,31)
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define BLACK 0

void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void delay(int n);

#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512

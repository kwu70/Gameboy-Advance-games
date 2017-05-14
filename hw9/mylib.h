//Kenny Wu

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#define REG_DISPCNT *(u16*)0x4000000
#define BG2_EN (1 << 10)
#define MODE_3 3
#define RGB(r,g,b) ((r) | ((g) << 5) | ((b) << 10))
#define OFFSET(r,c,rowL) (((r) * (rowL)) + (c))
#define SCANLINECOUNTER *(volatile unsigned short*)0x4000006

/* Colors */
#define BLACK 0
#define WHITE RGB(31,31,31)
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define MAGENTA RGB(31,0,31)
#define YELLOW RGB(31, 31, 0)
#define SILVER RGB(25, 25, 25)
#define GRAY RGB(15, 15, 15)

/* Buttons */
#define KEY_A      (1<<0)
#define KEY_B      (1<<1)
#define KEY_SELECT (1<<2)
#define KEY_START  (1<<3)
#define KEY_RIGHT  (1<<4)
#define KEY_LEFT   (1<<5)
#define KEY_UP     (1<<6)
#define KEY_DOWN   (1<<7)
#define KEY_R      (1<<8)
#define KEY_L      (1<<9)

#define BUTTONS *(volatile unsigned int*)0x04000130
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & (key))

/* DMA */
typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*)0x040000B0)

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

extern unsigned short *videoBuffer;

/* Prototypes */
void setPixel(int r, int c, u16 color);
void drawRect(int row, int col, int height, int width, u16 color);
void drawHollowRect(int row, int col, int height, int width, u16 color);
void delay(int n);
void waitForVblank();
void fillScreen(u16 color);
void drawQuad2Tri(int row, int col, int height, int width, u16 color);
void drawQuad4Tri(int row, int col, int height, int width, u16 color);
void drawImage3(int row, int col, int height, int width, const u16 *pic);
void fillScreen(volatile u16 color);



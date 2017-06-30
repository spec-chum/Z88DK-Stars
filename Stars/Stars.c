#include <stdlib.h>
#include <arch\zx.h>
#include <intrinsic.h>

#define NUMSTARS 68
#define NUMLAYERS 4

typedef unsigned char uchar;
typedef unsigned int uint;

struct Star
{
	uchar *yAddress;
	uchar x;
	uchar speed;
} stars[NUMSTARS];

void setUpStars()
{
	struct Star *currentStar = stars;

	while (currentStar != stars + sizeof(stars) / sizeof(*stars))
	{
		currentStar->yAddress = zx_py2saddr(rand() % 191);
		currentStar->x = rand() % 255;
		currentStar->speed = 1 + rand() % NUMLAYERS;
		
		*(currentStar->yAddress + (currentStar->x >> 3)) = zx_px2bitmask(currentStar->x);

		currentStar++;
	}
}

void drawStars()
{
	struct Star *currentStar = stars;

	while (currentStar != stars + sizeof(stars) / sizeof(*stars))
	{
		*(currentStar->yAddress + (currentStar->x >> 3)) ^= zx_px2bitmask(currentStar->x);
		currentStar->x -= currentStar->speed;
		*(currentStar->yAddress + (currentStar->x >> 3)) ^= zx_px2bitmask(currentStar->x);

		currentStar++;
	}
}

void main()
{
	intrinsic_ei();

	// Clear screen to black and set white ink
	zx_border(INK_BLACK);
	zx_cls(INK_WHITE);

	setUpStars();

	while (1)
	{
		zx_border(INK_CYAN);		
		drawStars();
		zx_border(INK_BLACK);
		intrinsic_halt();
	}
}

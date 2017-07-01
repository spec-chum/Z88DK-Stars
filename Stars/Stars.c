#include <stdlib.h>
#include <arch\zx.h>
#include <intrinsic.h>

#define NUMSTARS 75
#define NUMLAYERS 4

typedef unsigned char uchar;
typedef unsigned int uint;

struct Star
{
	uchar *yAddress;
	uchar bitmask;
	uchar x;
	uchar speed;
} stars[NUMSTARS];

void setUpStars()
{
	struct Star *currentStar = stars;

	while (currentStar != stars + sizeof(stars) / sizeof(*stars))
	{
		currentStar->yAddress = zx_py2saddr((uint)rand() % 191);
		currentStar->x = (uchar)rand();
		currentStar->bitmask = zx_px2bitmask(currentStar->x);
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
		*(currentStar->yAddress + (currentStar->x >> 3)) ^= currentStar->bitmask;
		currentStar->x -= currentStar->speed;
		*(currentStar->yAddress + (currentStar->x >> 3)) ^= (currentStar->bitmask = zx_px2bitmask(currentStar->x));

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

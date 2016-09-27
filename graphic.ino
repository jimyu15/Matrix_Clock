#include "RTClib.h"
#define MFIVE    0xF00000000000        // these are in hexadecimal
#define MTEN     0x5800000000000000
#define AQUARTER 0x80FE000000000000
#define TWENTY   0x7E00000000000000
#define HALF     0xF0000000000
#define PAST     0x7800000000
#define TO       0xC00000000
#define ONE      0x49
#define TWO      0xC040
#define THREE    0x1F0000
#define FOUR     0xF0
#define FIVE     0xF0000000
#define SIX      0xE00000
#define SEVEN    0x800F00
#define EIGHT    0x1F000000
#define NINE     0xF
#define TEN      0x1010100
#define ELEVEN   0x3F00
#define TWELVE   0xF600

void fillMatrix(uint32_t color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			setMatrix(j, i, color);
		}
	}
}

void drawMatrix(uint64_t bitmap, uint32_t color)
{
	uint64_t mask = 1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (mask & bitmap)
				setMatrix(j, 7 - i, color);
			mask *= 2;
		}
	}
}

void drawMatrix(uint64_t bitmap, uint32_t color1, uint32_t color2)
{
	int length = 0;
	for (int i = 0; i < 64; i++)
	{
		if (((uint64_t)1 << i) & bitmap)
			length++;
	}
	uint32_t *stripe = new uint32_t[length];
	for (int i = 0; i < length; i++)
	{
		uint32_t rr, gg, bb;
		rr = map (i, 0, length - 1, (color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF);
		gg = map (i, 0, length - 1, (color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF);
		bb = map (i, 0, length - 1, color1 & 0xFF, color2 & 0xFF);
		stripe[i] = (rr << 16) + (gg << 8) + bb;

	}
	int count = 0;
	uint64_t mask = 1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (mask & bitmap)
				setMatrix(j, 7 - i, stripe[count++]);
			mask *= 2;
		}
	}
	delete [] stripe;
}

void drawTime(DateTime time, uint32_t theme[])
{
	fillMatrix(0);
	uint64_t bitmap;
	switch (time.minute() / 5)
	{
		case 0:
		bitmap = 0;
		break;

		case 1:
		case 11:
		bitmap = MFIVE;
		break;

		case 2:
		case 10:
		bitmap = MTEN;
		break;

		case 3:
		case 9:
		bitmap = AQUARTER;
		break;

		case 4:
		case 8:
		bitmap = TWENTY;
		break;

		case 5:
		case 7:
		bitmap = TWENTY + MFIVE;
		break;

		case 6:
		bitmap = HALF;
		break;

		default:
		break;
	}
	drawMatrix(bitmap, theme[0], theme[1]);
	if (time.minute() >= 5)
		drawMatrix(time.minute() >= 35 ? TO : PAST, theme[2], theme[3]);

	switch ((time.hour() + time.minute() / 35) % 12)
	{
		case 0:
		bitmap = TWELVE;
		break;

		case 1:
		bitmap = ONE;
		break;

		case 2:
		bitmap = TWO;
		break;

		case 3:
		bitmap = THREE;
		break;

		case 4:
		bitmap = FOUR;
		break;

		case 5:
		bitmap = FIVE;
		break;

		case 6:
		bitmap = SIX;
		break;

		case 7:
		bitmap = SEVEN;
		break;

		case 8:
		bitmap = EIGHT;
		break;

		case 9:
		bitmap = NINE;
		break;

		case 10:
		bitmap = TEN;
		break;

		case 11:
		bitmap = ELEVEN;
		break;

		default:
		break;
	}
	drawMatrix(bitmap, theme[4], theme[5]);
	for (int i = 0; i < 4; i++)
		setCorner(i, (i < time.minute() % 5) ? theme[6] : 0);
	ledRefresh();
}
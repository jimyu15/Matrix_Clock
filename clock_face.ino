void simpleClock(uint32_t theme[])
{
	fillMatrix(0);
	drawTime(getTime(), theme);
	ledRefresh();
}

void clockWithSeconds(uint32_t theme[])
{
	DateTime now = getTime();
	fillMatrix(0);
	drawNumber(now.second(), 0xC0C0C0);
	drawTime(now, theme);
	ledRefresh();
}

void date()
{
	DateTime now = getTime();
	fillMatrix(0);
	drawMatrix(0xFFFF000000000000, 0xFF0000);
	drawSmallNumber(now.day(), 0xFFFFFF);
	ledRefresh();
}
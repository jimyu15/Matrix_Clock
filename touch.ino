#define SWIPEUP 8
#define SWIPEDOWN 9

const uint8_t touchPin[4] = {D5, D6, D7, D8};
volatile int touchPos = 0, touchStat = 0;
volatile uint32_t touchTime = 0;

void touchInit() 
{
	for (int i = 0; i < 4; i++)
	{
		pinMode(touchPin[i], INPUT);
		attachInterrupt(touchPin[i], touchPoll, CHANGE);
	}
}

int getTouchPos()
{
	uint8_t touchRead = 0;
	for (int i = 0; i < 4; i++)
	{
		touchRead *= 2;
		touchRead += digitalRead(touchPin[i]);
	}
	switch (touchRead)
	{
		case B0001:
		return 1;
		break;

		case B0011:
		return 2;
		break;

		case B0010:
		case B0111:
		return 3;
		break;

		case B0110:
		return 4;
		break;

		case B0100:
		case B1110:
		return 5;
		break;

		case B1100:
		return 6;
		break;

		case B1000:
		return 7;
		break;

		default:
		return 0;
		break;
	}
}

void touchPoll()
{
	static uint8_t swiped = 2;
	int touchRead = getTouchPos();
	
	if (touchPos == 0 && touchRead > 0)
	{
		touchTime = millis();
		touchPos = touchRead;
		swiped = 2;
		return;
	}

	else if (touchRead == 0 && touchPos > 0)
	{
		if (millis() - touchTime > 20 && millis() - touchTime < 500)
			touchStat = touchPos;
		swiped = 0;
	}

	else if (touchPos)
	{
		switch (touchRead - touchPos)
		{
			case 1:
			if (swiped)
				swiped--;
			else
				touchStat = SWIPEUP;
			break;

			case -1:
			if (swiped)
				swiped--;
			else
				touchStat = SWIPEDOWN;
			break;

			default:
			break;
		}
	}

	
	touchPos = touchRead;

}

uint8_t readTouch()
{
	uint8_t st = touchStat;
	touchStat = 0;
	return st;
}

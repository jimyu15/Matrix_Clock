#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void rtcInit()
{
	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
	}
	if (rtc.lostPower()) 
	{
    	rtc.adjust(DateTime(2016, 9, 27, 22, 13, 20));
	}
}

void setTime(int hr, int min, int sec)
{
	TimeSpan span(0, hr, min, sec);
	DateTime now = rtc.now() + span;
	rtc.adjust(now);
}

DateTime getTime()
{
	return rtc.now();
}
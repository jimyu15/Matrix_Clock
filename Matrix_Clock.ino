#include "RTClib.h"
void setup() 
{
  //adpsInit();
	rtcInit();
	ledInit();
	touchInit();
	Serial.begin(115200);
	Serial.println("Nice and cool");
	delay(100);
}

void loop()
{
	uint32_t theme[8] = {0xFF0000, 0xFFFF00, 0x00FF00, 0x00FFFF, 0xFFFFFF, 0x0000FF, 0xFF00FF, 0xFFFFFF};
	clockWithSeconds(theme);
	while (millis() % 1000 > 5)
		yield();
	
	
}
void loop1() 
{
  
  //getRGB();
  //Serial.println(getAmbientLight());
  Serial.println(getProximity());
  delay(100);
  
}

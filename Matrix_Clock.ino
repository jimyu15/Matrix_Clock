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
	uint32_t theme[8] = {0x00FF00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0xFFFFFF, 0x00FF00, 0xFFFFFF, 0xFFFFFF};
	drawTime(getTime(), theme);
	delay(1000);
	
	
	
}
void loop1() 
{
  
  //getRGB();
  //Serial.println(getAmbientLight());
  Serial.println(getProximity());
  delay(100);
  
}

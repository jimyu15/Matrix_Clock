#include <Colorduino.h>

void ColorFill(unsigned char R,unsigned char G,unsigned char B) 
{
  ColorRGB *p = Colorduino.GetPixel(0,0);
  for (unsigned char y=0;y<ColorduinoScreenWidth;y++) {
    for(unsigned char x=0;x<ColorduinoScreenHeight;x++) {
      p->r = R;
      p->g = G;
      p->b = B;
      p++;
    }
  }
  
  Colorduino.FlipPage();
}

void setup() 
{
  Colorduino.Init();
  unsigned char whiteBalVal[3] = {18,31,31};
  Colorduino.SetWhiteBal(whiteBalVal);
  ColorFill(255,255,255);
  Serial.begin(115200);

}

void loop() 
{
  while (Serial.available() < 2);
  if (Serial.read() == 'I')
  {
    char temp = Serial.read();
    if (temp == 'D')
    {
      uint8_t RGBBuffer[4];
      for (int i = 0; i < 4; i++)
      {
        uint16_t timeout = 2;
        while (!Serial.available())
        {
          if (timeout == 0)
          {
            Serial.println("timeout!");
            return;
          }
        }
        
        RGBBuffer[i] = Serial.read();
      }
      if (RGBBuffer[192] != 'E')
      {
        Serial.println("wrong data!");
        return;
      }
      Colorduino.SetWhiteBal(RGBBuffer);
    }
    if (temp == 'N')
    {
      uint8_t RGBBuffer[193];
      for (int i = 0; i < 193; i++)
      {
        uint16_t timeout = 2;
        while (!Serial.available())
        {
          if (timeout == 0)
          {
            Serial.println("timeout!");
            return;
          }
        }
        RGBBuffer[i] = Serial.read();
      }
      if (RGBBuffer[192] != 'E')
      {
        Serial.println("wrong data!");
        return;
      }
      for (int i = 0; i < 64; i++)
      {
        (Colorduino.curDrawFrame + i)->r = RGBBuffer[i * 3];
        (Colorduino.curDrawFrame + i)->g = RGBBuffer[i * 3 + 1];
        (Colorduino.curDrawFrame + i)->b = RGBBuffer[i * 3 + 2];
      }
      Colorduino.FlipPage();
    }
  }
  

}

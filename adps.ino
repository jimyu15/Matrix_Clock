#include <Wire.h>
#include <SparkFun_APDS9960.h>

#define APDS9960_INT    D3

SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void adpsInit() {

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }

  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_1X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }

}

void interruptRoutine()
{
  isr_flag = 1;
}

uint8_t getGesture()
{
  if ( isr_flag == 1 )
  {
    detachInterrupt(0);
    uint8_t result = 0;
    if ( apds.isGestureAvailable() )
      result = apds.readGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
    return result;
  }
  return 0;
}

uint32_t getRGB()
{
  uint16_t rgb[3] = {0, 0, 0};
  if (  !apds.readRedLight(rgb[0]) ||
        !apds.readGreenLight(rgb[1]) ||
        !apds.readBlueLight(rgb[2]) )
  {
    Serial.println("Error reading light values");
  }
  else
  {
    Serial.print("Red: ");
    Serial.print(rgb[0]);
    Serial.print(" Green: ");
    Serial.print(rgb[1]);
    Serial.print(" Blue: ");
    Serial.println(rgb[2]);
    uint16_t maximum = max(max(rgb[0], rgb[1]), rgb[2]);
    for (int i = 0; i < 3; i++)
    {
      uint32_t color = 255 * rgb[i] / maximum;
      rgb[i] = color;
    }
    Serial.print("Red: ");
    Serial.print(rgb[0]);
    Serial.print(" Green: ");
    Serial.print(rgb[1]);
    Serial.print(" Blue: ");
    Serial.println(rgb[2]);
  }
  return (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
}

uint16_t getAmbientLight()
{
  uint16_t ambient_light = 0;
  if (!apds.readAmbientLight(ambient_light))
  {
    Serial.println("Error reading light values");
  }
  return ambient_light;
}

uint8_t getProximity()
{
  uint8_t proximity_data = 0;
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  }
  return proximity_data;
}



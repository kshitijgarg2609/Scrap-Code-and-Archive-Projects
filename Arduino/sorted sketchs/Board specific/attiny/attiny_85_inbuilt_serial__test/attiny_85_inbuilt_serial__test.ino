#include <DigiCDC.h>
void setup()
{
  SerialUSB.begin();
  Serial.begin(9600);
}
void loop()
{
  if(Serial.available())
  {
    while(Serial.available())
    {
       char c=Serial.read();
       SerialUSB.write(c);
    }
  }
}

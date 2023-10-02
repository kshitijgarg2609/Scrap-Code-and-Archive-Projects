#include <SoftwareSerial.h>

SoftwareSerial ss(D6,D7);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
}

void loop()
{
  while(ss.available())
  {
    Serial.write(ss.read());
  }
  while(Serial.available())
  {
    ss.write(Serial.read());
  }
}

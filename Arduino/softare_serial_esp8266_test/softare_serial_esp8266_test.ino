#include <SoftwareSerial.h>

SoftwareSerial vserial(D1,D2);

void setup()
{
  Serial.begin(115200);
  vserial.begin(115200);
}

void loop()
{
  while(Serial.available())
  {
    vserial.write(Serial.read());
  }
  while(vserial.available())
  {
    Serial.write(vserial.read());
  }
}

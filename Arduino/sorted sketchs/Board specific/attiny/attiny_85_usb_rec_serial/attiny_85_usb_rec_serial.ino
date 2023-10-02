#include <DigiCDC.h>

long snp;

void setup()
{
  SerialUSB.begin();
  Serial.begin(9600);
  snp=millis();
}

void loop()
{
  //Serial.println("Check !!!");
  //delay(2000);
  //serial();

  if((millis()-snp)>=2000)
  {
    Serial.println("check");
    snp=millis();
  }
  
  if(Serial.available())
  {
    while(Serial.available())
    {
      uint8_t x=Serial.read();
      Serial.println(x);
      SerialUSB.write(x);
    }
  }
}

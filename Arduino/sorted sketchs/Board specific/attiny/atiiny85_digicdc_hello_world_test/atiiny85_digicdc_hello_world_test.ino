#include <DigiCDC.h>
void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin();
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  Serial.println(F("Tested !!!"));
}

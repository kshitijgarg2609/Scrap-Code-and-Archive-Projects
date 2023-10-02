#include <DigiKeyboard.h>
//#include <SoftwareSerial.h>
//#include <TinyPinChange.h>
//#include <Wire.h>
//SoftSerial sp(0,1);

void setup()
{
  DigiKeyboard.sendKeyStroke(0);
  //SerialUSB.begin();
  //sp.begin(9600);
}

void loop()
{
  DigiKeyboard.println("Hello Digispark!");
}

#include <SoftwareSerial.h>
#include <SIM800L.h>

SoftwareSerial vserial(D2,D1);
SIM800L gsm;

char number[]="+919212722296";

long snp=0;

void setup()
{
  Serial.begin(9600);
  vserial.begin(9600);
  if(gsm.begin(vserial))
  {
    Serial.println("GSM CONNECTED !!!");
  }
  else
  {
    Serial.println("GSM NOT CONNECTED !!!");
  }
}

void loop()
{
  if((millis()-snp)>=500)
  {
    Serial.println("CHECK");
    printStatus();
    snp=millis();
  }
}

void printStatus()
{
  String np=gsm.serviceProvider();
  delay(50);
  String ss="Signal Strength : "+String(gsm.signalStrength());
  delay(50);
  String cs="Call Status : "+String(gsm.callStatus());
  delay(50);
  String inc=(gsm.incomingCall())?"INCOMING CALL":"NO INCOMING CALL";
  delay(50);
  Serial.println(np+" ,"+ss+" ,"+cs+" ,"+inc);
}

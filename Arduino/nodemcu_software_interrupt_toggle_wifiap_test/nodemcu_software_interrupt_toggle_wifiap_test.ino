#include <ESP8266WiFi.h>

int pin=0;
int led=1;
boolean flg=true;
boolean wflg=false;

void setup()
{
  Serial.begin(115200);
  pinMode(pin,INPUT_PULLUP);
  digitalWrite(pin,HIGH);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  WiFi.mode(WIFI_AP);
}

void loop()
{
  interruptFunction();
}

void interruptFunction()
{
  boolean cflg=(digitalRead(pin)==HIGH);
  if(flg==cflg)
  {
    return;
  }
  flg=cflg;
  if(!flg)
  {
    toggle();
  }
}

void toggle()
{
  if(wflg)
  {
    WiFi.softAP("k","123456789");
    digitalWrite(led,LOW);
    wflg=false;
  }
  else
  {
    WiFi.softAPdisconnect();
    digitalWrite(led,HIGH);
    wflg=true;
  }
}

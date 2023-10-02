#include <ESP8266WiFi.h>

boolean flg=true;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("k","123456789");
  WiFi.begin("xyz","123456789");
  operateAP();
  //attachInterrupt(digitalPinToInterrupt(D4),operateAP,HIGH);
}

void operateAP()
{
  if(flg)
  {
    WiFi.softAPdisconnect(true);
    flg=false;
  }
  else
  {
    WiFi.softAPdisconnect(false);
    flg=true;
  }
}

void loop()
{
  if(WiFi.isConnected())
  {
    Serial.println("WiFi Connected !!!");
  }
  else
  {
    Serial.println("WiFi Disconnected !!!");
  }
  Serial.println("Stations connected :- "+String(WiFi.softAPgetStationNum()));
  delay(800);
}

#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("k","123456789");
  WiFi.begin("xyz","123456789");
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

#include <ESP8266WiFi.h>
void setup()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin("K","123456789");
  WiFi.softAP("xyz","123456789");
}

void loop()
{
  
}

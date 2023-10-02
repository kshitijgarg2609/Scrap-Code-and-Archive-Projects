//#include<ESP8266WiFi.h>
#include <WiFi.h>
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("sabka baap","sabkabaap2609");
}

void loop()
{
  if(WiFi.isConnected())
  {
    Serial.println("CONNECTED");
  }
  else
  {
    Serial.println("NOT CONNECTED");
  }
  delay(1000);
}

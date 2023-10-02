#include<ESP8266WiFi.h>

int i;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("k","123456789");
  WiFi.begin("sabka baap","sabkabaap2607");
}

void loop()
{
  i=WiFi.softAPgetStationNum();
  Serial.println("WiFi connected :- "+String(i));
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

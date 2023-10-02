#include<ESP8266WiFi.h>

int i;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("k","123456789");
}

void loop()
{
  i=WiFi.softAPgetStationNum();
  Serial.println("WiFi connected :- "+String(i));
  delay(1000);
}

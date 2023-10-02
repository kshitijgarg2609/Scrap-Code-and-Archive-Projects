#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

WiFiUDP udp;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  udp.begin(4210);
  Serial.begin(115200);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    processPacket(i);
  }
}

void processPacket(int a)
{
  uint8_t rdata[a];
  udp.read(rdata,a);
  String tmp="";
  for(int i=0;i<a;i++)
  {
    tmp+=(char)(rdata[i]);
  }
  cmd(tmp);
}

void cmd(String a)
{
  Serial.println(a);
}

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

WiFiUDP udp;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  udp.begin(4210);
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
  tmp=cmd(tmp);
  udp.beginPacket(udp.remoteIP(),udp.remotePort());
  for(int i=0;i<tmp.length();i++)
  {
    udp.write((uint8_t)(tmp.charAt(i)));
  }
  udp.endPacket();
}

String cmd(String a)
{
  return a;
}

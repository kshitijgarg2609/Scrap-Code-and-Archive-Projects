#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

WiFiUDP udp;

void setup()
{
  WiFi.begin("sabka baap","sabkabaap2609");
  udp.begin(4210);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    uint8_t rdata[i];
    udp.read(rdata,i);
    udp.beginPacket(udp.remoteIP(),udp.remotePort());
    udp.write(rdata,i);
    udp.endPacket();
  }
}

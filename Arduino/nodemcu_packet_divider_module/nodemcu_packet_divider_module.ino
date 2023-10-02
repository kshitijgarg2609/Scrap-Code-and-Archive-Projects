#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "PacketFragmentModule.h"

WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  WiFi.begin("sabka baap","sabkabaap2609");
  udp.begin(4210);
  Serial.begin(115200);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    uint8_t rdata[i];
    udp.read(rdata,i);
    initPacketDivider(i);
    for(int j=0;j<i;j++)
    {
      if(writePacket(rdata[j])==1)
      {
        udp.beginPacket(udp.remoteIP(),udp.remotePort());
        udp.write(pkt,pkt_length);
        udp.endPacket();
      }
    }
  }
}

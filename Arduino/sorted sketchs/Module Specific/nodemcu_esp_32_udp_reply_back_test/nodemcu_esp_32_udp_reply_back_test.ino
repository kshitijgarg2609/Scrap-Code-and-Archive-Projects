#include <WiFi.h>
#include <WiFiUdp.h>

int i;

IPAddress arr(192,168,2,1);
IPAddress subnet(255,255,255,0);

WiFiUDP Udp;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(arr,arr,subnet);
  i=WiFi.softAP("K","123456789");
  Udp.begin(4210);
}

void loop()
{
  i=Udp.parsePacket();
  if(i>0)
  {
    uint8_t rdata[i];
    Udp.read(rdata,i);
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(rdata,i);
    Udp.endPacket();
  }
}

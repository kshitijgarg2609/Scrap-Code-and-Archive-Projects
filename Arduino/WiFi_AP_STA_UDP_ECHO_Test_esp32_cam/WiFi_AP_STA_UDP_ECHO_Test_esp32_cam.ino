#include <WiFi.h>

WiFiUDP udp;

//IPAddress ip(192,168,26,1);
//IPAddress subnet(255,255,255,1);

void setup()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("K","123456789");
  WiFi.begin("sabka baap","sabkabaap2609");
  //WiFi.softAPConfig(ip,ip,subnet);
  
  udp.begin(4210);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    uint8_t dta[i];
    udp.read(dta,i);
    udp.beginPacket(udp.remoteIP(),udp.remotePort());
    udp.write(dta,i);
    udp.endPacket();
  }
}

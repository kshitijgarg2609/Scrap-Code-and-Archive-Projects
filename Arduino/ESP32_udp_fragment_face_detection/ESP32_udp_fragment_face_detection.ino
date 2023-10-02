#include <WiFi.h>
#include "PacketFragmentModule.h"
#include "camera_frame_data.h"

IPAddress rem_ip;
unsigned int rem_port;

WiFiUDP udp;

void setup()
{
  WiFi.mode(WIFI_AP);
  //WiFi.softAPConfig(ip,ip,subnet);
  WiFi.softAP("K","123456789");
  //WiFi.begin("sabka baap","sabkabaap2609");
  initCam();
  udp.begin(4210);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    //udp.beginPacket(udp.remoteIP(),udp.remotePort());
    uint8_t rdata[i];
    udp.read(rdata,i);
    rem_ip=udp.remoteIP();
    rem_port=udp.remotePort();
    if(i==1&&rdata[0]=='F')
    {
      if(getFrame()==1)
      {
        
        unsigned int flen=frame->len;
        initPacketDivider(flen);
        for(i=0;i<flen;i++)
        {
          if(writePacket(frame->buf[i])==1)
          {
            
            udp.beginPacket(rem_ip,rem_port);
            udp.write(pkt,pkt_len);
            udp.endPacket();
          }
        }
      }
      else
      {
        udp.beginPacket(udp.remoteIP(),udp.remotePort());
        udp.write((uint8_t)('N'));
        udp.endPacket();
      }
    }
    else
    {
      udp.beginPacket(udp.remoteIP(),udp.remotePort());
      udp.write((uint8_t)('E'));
      udp.endPacket();
    }
  }
}

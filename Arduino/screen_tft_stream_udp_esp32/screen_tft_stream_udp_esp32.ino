#include <WiFi.h>
#include "PacketCollectorModule.h"
#include "TFT_eSPI.h"
#include "TFT_eFEX.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eFEX  fex = TFT_eFEX(&tft);
WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  initPacketCollectorModule(20480);
  WiFi.softAP("K","123456789");
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_GREEN);
  udp.begin(4210);
}

void loop()
{
  processPacket();
}

void processPacket()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    uint8_t rdata[i];
    udp.read(rdata,i);
    if(decodePacket(rdata,i))
    {
      if(fex.drawJpg(bytebuffer,getQueueSize()))
      {
        Serial.println("FRAME PRINTED !!!");
      }
      else
      {
        Serial.println("FRAME NOT PRINTED !!!");
      }
    }
  }
}

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <RF24.h>

WiFiUDP udp;

IPAddress rem_ip(192,168,4,255);
unsigned int rem_port=4210;

RF24 radio(D2,D3);

uint8_t addr1[] = {0,1,2,0,9};
uint8_t addr2[] = {9,0,2,1,0};

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  udp.begin(4210);
  Serial.begin(115200);
}

void loop()
{
  operateUdp();
  operateRadio();
}

void operateUdp()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    Serial.println("Sending Over Radio");
    uint8_t rdata[i];
    udp.read(rdata,i);
    rem_ip=udp.remoteIP();
    rem_port=udp.remotePort();
    radio.stopListening();
    radio.write(rdata,i);
    radio.startListening();
  }
}

void operateRadio()
{
  while(radio.available(addr2))
  {
    uint8_t rdata[32];
    radio.read(rdata, sizeof(rdata));
    //radio.flush_rx();
    uint8_t rlen=0;
    if(rdata[1]=='F')
    {
      rlen=rdata[10]+11;
    }
    else if(rdata[1]=='M' || rdata[1]=='L')
    {
      rlen=rdata[8]+9;
    }
    else if(rdata[1]=='N')
    {
      rlen=rdata[3]+4;
    }
    Serial.println(String(rlen));
    //radio.stopListening();
    //delayMicroseconds(20);
    udp.beginPacket(rem_ip,rem_port);
    udp.write(rdata,rlen);
    udp.endPacket();
    
    //radio.startListening();
  }
  if(!radio.isChipConnected())
  {
    initRF();
  }
}

void initRF()
{
  if(radio.begin())
  {
    radio.setDataRate(RF24_2MBPS);
    //radio.setAutoAck(false);
    //radio.setRetries(2,5);
    radio.openWritingPipe(addr1);
    radio.openReadingPipe(1, addr2);
    radio.startListening();
    Serial.println("Radio Started !!!");
  }
  else
  {
    Serial.println("Radio couldn't start !!!");
  }
}

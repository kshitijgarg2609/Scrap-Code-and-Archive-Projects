#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <RF24.h>
#include "PacketCollectorModule.h"
#include "PacketFragmentModule.h"

WiFiUDP udp;

IPAddress rem_ip(192,168,4,255);
unsigned int rem_port=4210;

RF24 radio(D2,D3);

uint8_t addr1[] = {0,1,2,0,9};
uint8_t addr2[] = {9,0,2,1,0};

long snp;
long timeout=100;
boolean sender_flg=false;

uint8_t pkt_stor[1024];
int pkt_stor_siz=0;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  udp.begin(4210);
  Serial.begin(115200);
  initPacketDividerModule('F',10240,1280);
  initPacketCollectorModule(10240);
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
    //Serial.println("Sending Over Radio");
    uint8_t rdata[i];
    udp.read(rdata,i);
    rem_ip=udp.remoteIP();
    rem_port=udp.remotePort();
    pkt_stor_siz=i;
    for(int j=0;j<i;j++)
    {
      pkt_stor[j]=rdata[j];
    }
  }
  if(!sender_flg&&(millis()-snp)>timeout)
  {
    snp=millis();
    sender_flg=true;
  }
  if(sender_flg)
  {
    if(pkt_stor_siz>0)
    {
      radio.stopListening();
      radio.write(pkt_stor,pkt_stor_siz);
      radio.startListening();
    }
    pkt_stor_siz=0;
    sender_flg=false;
  }
}

void operateRadio()
{
  //radio.startListening();
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
    //Serial.println(String(rlen));
    sendAcknowledge();
    if(decodePacket(rdata,rlen))
    {
      Serial.println("+++"+String(getQueueSize()));
      sender_flg=true;
      sendCollectedPackets();
    }
    snp=millis();
    //radio.stopListening();
    //delayMicroseconds(20);
    /*
    udp.beginPacket(rem_ip,rem_port);
    udp.write(rdata,rlen);
    udp.endPacket();
    */
    
    //radio.startListening();
  }
  if(!radio.isChipConnected())
  {
    initRF();
  }
}

void sendAcknowledge()
{
  char ack[32]="ack";
  radio.stopListening();
  radio.write(ack,3);
  radio.startListening();
}

void sendCollectedPackets()
{
  initPacketDivider(getQueueSize());
  for(int i=0;i<getQueueSize();i++)
  {
    uint8_t xx=bytebuffer[i];
    //Serial.printf("bb[%d]=%d\n",i,xx);
    if(writePacket(xx))
    {
      udp.beginPacket(rem_ip,rem_port);
      udp.write(pkt,pkt_len);
      udp.endPacket();
    }
  }
}

void initRF()
{
  if(radio.begin())
  {
    radio.setDataRate(RF24_2MBPS);
    radio.setAutoAck(false);
    //radio.setRetries(2,5);
    radio.disableAckPayload();
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

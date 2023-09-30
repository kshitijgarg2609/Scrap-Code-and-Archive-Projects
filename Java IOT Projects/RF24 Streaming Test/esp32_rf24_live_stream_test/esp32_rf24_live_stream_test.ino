#include <SPI.h>
#include <RF24.h>
#include "PacketFragmentModule.h"
#include "camera_frame_data.h"

RF24 radio(2,15);
uint8_t addr1[] = {0,1,2,0,9};
uint8_t addr2[] = {9,0,2,1,0};

void setup()
{
  Serial.begin(115200);
  initCam();
  initPacketDividerModule('F',10240,21);
  initRF();
}

void loop()
{
  radioCmd();
}

void initRF()
{
  SPI.begin(14,12,13,15);
  if(radio.begin())
  {
    radio.setDataRate(RF24_2MBPS);
    //radio.setAutoAck(false);
    radio.setRetries(0,0);
    radio.openWritingPipe(addr2);
    radio.openReadingPipe(1, addr1);
    radio.startListening();
    Serial.println("Radio Started !!!");
  }
  else
  {
    Serial.println("Radio couldn't start !!!");
  }
}

void radioCmd()
{
  if (radio.available())
  {
    char text[32] = "";
    radio.read(text, sizeof(text));
    //Serial.println(String(text));
    cmd(String(text));
  }
  if(!radio.isChipConnected())
  {
    initRF();
  }
}

void cmd(String a)
{
  if(a.equals("frame"))
  {
    if(getFrame()==1)
    {
      long e1=millis();
      radio.stopListening();
       unsigned int flen=frame->len;
       initPacketDivider(flen);
       for(unsigned int i=0;i<flen;i++)
       {
         if(writePacket(frame->buf[i])==1)
         {
           int cnt_down=30;
           //delayMicroseconds(10);
           
           do
           {
             cnt_down--;
             if(radio.write(pkt,pkt_len))
             {
               cnt_down=-1;
               //Serial.println("FRAGMENT SENT !!!");
               //delayMicroseconds(40);
             }
             else
             {
               //Serial.println("FRAGMENT RETYING _______________________________ !!!");
               //delayMicroseconds(400);
             }
           }
           while(cnt_down>0);
           if(cnt_down!=-1)
           {
             Serial.println("FRAMENT FAILED TO SEND !!! _____________________________________________________________________________________");
             i=flen;
           }
           /*
           if(radio.write(pkt,pkt_len))
           {
            
           }
           else
           {
            Serial.println("Fragment missed");
            i=flen;
           }
           */
           //delayMicroseconds(20);
           
         }
       }
       radio.startListening();
       long e2=millis();
       long e3=e2-e1;
       Serial.println(String(e3));
    }
  }
}

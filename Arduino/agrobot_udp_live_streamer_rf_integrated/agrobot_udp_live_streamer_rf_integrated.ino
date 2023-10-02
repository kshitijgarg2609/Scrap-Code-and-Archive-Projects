#include <WiFi.h>
#include "PacketFragmentModule.h"
#include "camera_frame_data.h"

IPAddress rem_ip(192,168,4,2);
unsigned int rem_port=4210;

WiFiUDP udp;

String sdata="";
String edata="";
boolean s_flg=false;
boolean e_flg=false;
uint8_t cm_flg=0;

String rxdata="";
long snp;
long rxto=500;
boolean rx_flg=false;


void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  //WiFi.mode(WIFI_STA);
  //WiFi.begin("xyz","123456789");
  Serial.begin(115200);
  initCam();
  udp.begin(4210);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    //udp.beginPacket(udp.remoteIP(),udp.remotePort());
    rem_ip=udp.remoteIP();
    rem_port=udp.remotePort();
    if(decodePacket(i))
    {
       encodePacket();
    }
  }
  if(!rx_flg)
  {
    rxdata=rxSerial();
    if(rxdata!="")
    {
      rx_flg=true;
    }
  }
  /*
  if(!rx_flg&&Serial.available())
  {
    rxdata=rxSerial();
    rx_flg=true;
  }
  */
}

boolean decodePacket(int a)
{
  uint8_t rdata[a];
  udp.read(rdata,a);
  if((a<6)||(rdata[0]!=(char)('A')||rdata[1]!=(char)('R')))
  {
    return false;
  }
  uint16_t sl,el,i;
  sl=rdata[2]<<8 | rdata[3];
  el=rdata[4]<<8 | rdata[5];
  if((6+sl+el)!=a)
  {
    return false;
  }
  String sdata="";
  String edata="";
  if(sl!=0)
  {
    for(i=6;i<6+sl;i++)
    {
      sdata+=(char)(rdata[i]);
    }
    s_flg=true;
    Serial.println(sdata);
    //while(!Serial.available());
    //rxdata=rxSerial();
  }
  if(el!=0)
  {
    for(i=6+sl;i<a;i++)
    {
      edata+=(char)(rdata[i]);
    }
    cmd(edata);
  }
  return true;
}

String rxSerial()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  return m;
}

void cmd(String a)
{
  if(a.equals("frame"))
  {
    e_flg=true;
    if(getFrame()==1)
    {
      cm_flg=1;
    }
    else
    {
      cm_flg=2;
    }
  }
}



void encodePacket()
{
  uint16_t sl=0,el=0,flen,i,t=0;
  boolean ots=false;
  if(s_flg)
  {
    sdata=rxdata;
    rx_flg=false;
    if(sdata!="")
    {
      sl=sdata.length();
      t+=sl;
    }
  }

  if(cm_flg==1)
  {
    edata="jpg:";
    flen=frame->len;
    el=edata.length()+flen;
  }
  else if(cm_flg==2)
  {
    edata="frame error";
    el=edata.length();
  }
  else if(e_flg)
  {
    el=edata.length();
  }
  t+=el;

  initPacketDivider(6+t);
  writePacket((uint8_t)('A'));
  writePacket((uint8_t)('R'));
  writePacket((uint8_t)(sl>>8));
  writePacket((uint8_t)(sl));
  writePacket((uint8_t)(el>>8));
  writePacket((uint8_t)(el));

  if(sl!=0)
  {
    for(i=0;i<sdata.length();i++)
    {
      if(writePacket((uint8_t)(sdata.charAt(i)))==1)
      {
        udp.beginPacket(rem_ip,rem_port);
        udp.write(pkt,pkt_len);
        udp.endPacket();
        ots=true;
      }
    }
  }

  if(el!=0)
  {
    if(e_flg)
    {
      for(i=0;i<edata.length();i++)
      {
        if(writePacket((uint8_t)(edata.charAt(i)))==1)
        {
          udp.beginPacket(rem_ip,rem_port);
          udp.write(pkt,pkt_len);
          udp.endPacket();
          ots=true;
        }
      }
    }
    if(cm_flg==1)
    {
      for(i=0;i<flen;i++)
      {
        if(writePacket(frame->buf[i])==1)
        {
          udp.beginPacket(rem_ip,rem_port);
          udp.write(pkt,pkt_len);
          udp.endPacket();
          ots=true;
        }
      }
    }
  }

  if(!ots)
  {
    udp.beginPacket(rem_ip,rem_port);
    udp.write(pkt,pkt_len);
    udp.endPacket();
  }
  cm_flg=0;
  s_flg=false;
  e_flg=false;
  
}

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#include "SmartRackPins.h"


WiFiUDP udp;



void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Smart Rack Inventory","123456789");
  udp.begin(4210);
  initSystem();
}

void loop()
{
  process();
  int i=udp.parsePacket();
  if(i>0)
  {
    processPacket(i);
  }
}

void processPacket(int a)
{
  uint8_t rdata[a];
  udp.read(rdata,a);
  String tmp="";
  for(int i=0;i<a;i++)
  {
    tmp+=(char)(rdata[i]);
  }
  tmp=cmd(tmp);
  udp.beginPacket(udp.remoteIP(),udp.remotePort());
  for(int i=0;i<tmp.length();i++)
  {
    udp.write((uint8_t)(tmp.charAt(i)));
  }
  udp.endPacket();
}

String cmd(String a)
{
  char fil,sch,wst;
  int add;
  int len=a.length();
  DateTime ftch;
  if(len==10&&a.equals("connection"))
  {
    return "connected";
  }
  else if(len==7&&a.equals("request")==true)
  {
    char fetch[]="DD-MM-YYYY hh:mm:ss";
    dt=rtc.now();
    dt.format(fetch);
    return String(fetch);
  }
  else if(len==23&&a.indexOf("set:")!=-1)
  {
    dt=DateTime(a.substring(4,14).c_str(),a.substring(15).c_str());
    rtc.adjust(dt);
    return "set:";
  }
  else if(len==6&&a.equals("button"))
  {
    return pushState();
  }
  else if(len==3&&a.equals("fan"))
  {
    return ("fan:"+String(fan));
  }
  else if(len==3&&a.equals("dht"))
  {
    return dht();
  }
  else if(len>=12&&a.indexOf("sch")!=-1)
  {
    int indx1d=a.indexOf("d");
    int indx2h=a.lastIndexOf("h");
    int indx3m=a.indexOf("m");
    int indx4s=a.lastIndexOf("s");
    if(indx1d==-1||indx2h==-1||indx3m==-1||indx4s==-1)
    {
      return "ERR";
    }
    int sdate=a.substring(indx1d+1,indx2h).toInt();
    int shrs=a.substring(indx2h+1,indx3m).toInt();
    int smin=a.substring(indx3m+1,indx4s).toInt();
    int ssec=a.substring(indx4s+1).toInt();
    if(!((sdate>=0)&&(shrs>=0&&shrs<24)&&(smin>=0&&smin<60)&&(ssec>=0&&ssec<60)))
    {
      return "ERR";
    }
    td=TimeDelta(sdate,shrs,smin,ssec);
    p=rtc.now()+td;
    dur=true;
    return "sch:";
  }
  else if(len==9&&a.equals("remaining"))
  {
    String rem="remaining:";
    for(int i=0;i<6;i++)
    {
      fil=arr[i].fil;
      sch=arr[i].sch;
      wst=arr[i].wst;
      if(wst=='1')
      {
        rem+="w";
      }
      else if(fil=='1'&&sch=='1')
      {
        td=arr[i].dt-rtc.now();
        rem+=String(td.totalseconds());
      }
      else
      {
        rem+=(String(0));
      }
      rem+=":";
    }
    return rem;
  }
  /*
  else if(len==4&&a.equals("test"))
  {
    for(int lp=0;lp<6;lp++)
    {
      add=base+(10*lp);
      EEPROM.get(add,fil);
      EEPROM.get(add+1,sch);
      EEPROM.get(add+2,wst);
      EEPROM.get(add+3,ftch);
      char fetch[100]="DD-MM-YYYY hh:mm:ss";
      ftch.format(fetch);
      Serial.println("Number :- "+String(lp));
      Serial.println(String(fil));
      Serial.println(String(sch));
      Serial.println(String(wst));
      Serial.println(String(fetch));
    }
  }
  */
  else if(len==5&&a.equals("erase"))
  {
    setDefault();
    return "erased";
  }  
  return "#";
}

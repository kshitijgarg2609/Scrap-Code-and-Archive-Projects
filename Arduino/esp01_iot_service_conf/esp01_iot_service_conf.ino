#include "WiFiEEPROMModule.h"
#include "WSHandler.h"

//Process
long con_to=500;
long ping_send_to=5000;
long ping_rec_wait=2000;

long snp;

void setup()
{
  Serial.begin(115200);
  initUdp();
  clnt.onMessage(onMessageCallback);
  clnt.onEvent(onEventsCallback);
  initEEPROMProcess();
}

void loop()
{
  if(udpPacket())
  {
    cmd(udp_data,true);
  }
  if(stat_actv)
  {
    wcon=true;
    if(wcon)
    {
      if(wscon)
      {
        clnt.poll();
        if(ping_flg&&((millis()-snp)>=ping_send_to))
        {
          updateSnapTime();
          clnt.send("P#@");
          ping_flg=false;
          ping_chk=false;
          clnt.poll();
          if(!dcon)
          {
            clnt.send(auth_key_str);
          }
        }
        if(!ping_flg)
        {
          if(ping_chk)
          {
            ping_flg=true;
          }
          else if((millis()-snp)>=ping_rec_wait)
          {
            updateSnapTime();
            wscon=false;
            ping_flg=true;
          }
        }
      }
      else
      {
        ping_flg=true;
        dcon=false;
        rcon=false;
        if((millis()-snp)>=con_to)
        {
          if(!wscon&&cnfg)
          {
            replyBack("S:SERVER OFFLINE");
          }
          clnt.connect(ws_link_str);
          updateSnapTime();
        }
      }
    }
  }
  else
  {
    wscon=false;
    dcon=false;
    rcon=false;
  }
  serialEvent();
}

void cmd(String a,boolean udp_f)
{
  if(!cnfg)
  {
    if(a.equals("config"))
    {
      cnfg=true;
      udp_flg=udp_f;
      replyBack("ENTERED CONFIGURATION MODE");
      return;
    }
    clnt.sendBinary("X:"+a);
    return;
  }
  if(udp_flg!=udp_f)
  {
    return;
  }
  if(a.indexOf("X:")==0)
  {
    clnt.sendBinary(a.substring(2));
  }
  else if(a.equals("activate"))
  {
    ON();
    replyBack("DEVICE ACTIVATED");
  }
  else if(a.equals("deactivate"))
  {
    clnt.close();
    OFF();
    replyBack("DEVICE DEACTIVATED");
  }
  else if(a.indexOf("set#wifi_ssid:")!=-1)
  {
    setWFID(a.substring(14));
    replyBack("WIFI SSID UPDATED");
  }
  else if(a.indexOf("set#wifi_key:")!=-1)
  {
    setKey(a.substring(13));
    replyBack("WIFI SSID KEY UPDATED");
  }
  else if(a.equals("get#wifi_ssid"))
  {
    replyBack("wifi_ssid :- "+loadWFID());
  }
  else if(a.equals("get#wifi_key"))
  {
    String wfkey=loadKey();
    if(loadKey().equals(""))
    {
      wfkey="NULL";
    }
    replyBack("wifi_key :- "+wfkey);
  }
  else if(a.indexOf("set#authkey:")!=-1)
  {
    setAuthKey(a.substring(12));
    replyBack("AUTHENTICATION KEY UPDATED");
  }
  else if(a.equals("get#authkey"))
  {
    replyBack("AUTHENTICATION KEY :- "+loadAuthKey());
  }
  else if(a.indexOf("set#wslink:")!=-1)
  {
    setWSLink(a.substring(11));
    replyBack("WS LINK UPDATED");
  }
  else if(a.equals("get#wslink"))
  {
    replyBack("WS LINK :- "+loadWSLink());
  }
  else if(a.equals("erase"))
  {
    erase();
    replyBack("DEVICE SET TO DEFAULT");
  }
  else if(a.equals("exit"))
  {
    cnfg=false;
    replyBack("CONFIGURATION MODE EXIT");
    udp_flg=false;
  }
  else if(a.equals("CHECK DEVICE"))
  {
    replyBack(model+"@"+service);
  }
  else
  {
    replyBack("INVALID COMMAND");
  }
}

void updateSnapTime()
{
  snp=millis();
}

//#############################################################################################
void serialEvent()
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
  if(m=="")
  {
    return;
  }
  cmd(m,false);
}

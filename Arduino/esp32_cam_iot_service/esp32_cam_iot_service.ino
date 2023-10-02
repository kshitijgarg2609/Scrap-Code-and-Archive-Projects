#include "WiFiESP32EEPROMModule.h"
#include "WSHandler.h"

//Process
long con_to=500;
long ping_send_to=10000;
long ping_rec_wait=2000;

long snp;


void setup()
{
  Serial.begin(115200);
  clnt.onMessage(onMessageCallback);
  clnt.onEvent(onEventsCallback);
  startProcess();
  initEEPROMProcess();
}

void loop()
{
  if(stat_actv)
  {
    wcon=(WiFi.status()==WL_CONNECTED);
    //delay(500);
    if(frame_send&&rcon)
    {
      sendLiveFrames();
    }
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
            Serial.println("S:SERVER OFFLINE");
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

void cmd(String a)
{
  if(!cnfg)
  {
    if(a.equals("config"))
    {
      cnfg=true;
      Serial.println("ENTERED CONFIGURATION MODE");
      return;
    }
    clnt.sendBinary("X:"+a);
    return;
  }
  if(a.indexOf("X:")==0)
  {
    clnt.sendBinary(a.substring(2));
  }
  else if(a.equals("activate"))
  {
    ON();
    Serial.println("DEVICE ACTIVATED");
  }
  else if(a.equals("deactivate"))
  {
    clnt.close();
    OFF();
    Serial.println("DEVICE DEACTIVATED");
  }
  else if(a.indexOf("set#wifi_ssid:")!=-1)
  {
    setWFID(a.substring(14));
    Serial.println("WIFI SSID UPDATED");
  }
  else if(a.indexOf("set#wifi_key:")!=-1)
  {
    setKey(a.substring(13));
    Serial.println("WIFI SSID KEY UPDATED");
  }
  else if(a.equals("get#wifi_ssid"))
  {
    Serial.println("wifi_ssid :- "+loadWFID());
  }
  else if(a.equals("get#wifi_key"))
  {
    String wfkey=loadKey();
    if(loadKey().equals(""))
    {
      wfkey="NULL";
    }
    Serial.println("wifi_key :- "+wfkey);
  }
  else if(a.indexOf("set#authkey:")!=-1)
  {
    setAuthKey(a.substring(12));
    Serial.println("AUTHENTICATION KEY UPDATED");
  }
  else if(a.equals("get#authkey"))
  {
    Serial.println("AUTHENTICATION KEY :- "+loadAuthKey());
  }
  else if(a.indexOf("set#wslink:")!=-1)
  {
    setWSLink(a.substring(11));
    Serial.println("WS LINK UPDATED");
  }
  else if(a.equals("get#wslink"))
  {
    Serial.println("WS LINK :- "+loadWSLink());
  }
  else if(a.equals("erase"))
  {
    erase();
    Serial.println("DEVICE SET TO DEFAULT");
  }
  else if(a.equals("exit"))
  {
    cnfg=false;
    Serial.println("CONFIGURATION MODE EXIT");
  }
  else
  {
    Serial.println("INVALID COMMAND");
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
  cmd(m);
}

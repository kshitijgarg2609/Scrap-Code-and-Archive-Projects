#include <EEPROM.h>
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

String ws_link_str;
String auth_key_str;

boolean cnfg=false;

boolean wcon=false;
boolean wscon=false;
boolean dcon=false;
boolean rcon=false;

boolean ping_flg=true;
boolean ping_chk=false;

long con_to=500;
long ping_send_to=10000;
long ping_rec_wait=2000;

boolean stat_actv;
int code,actv,base,wssid,wkey,wslink,authkey;
int li;

long snp;

using namespace websockets;
WebsocketsClient clnt;

void onMessageCallback(WebsocketsMessage message)
{
    String msg=message.data();
    if(msg.charAt(0)=='D')
    {
      if(!cnfg)
      {
        msg=msg.substring(2);
      }
      Serial.println(msg);
    }
    else if(msg.charAt(0)=='S')
    {
      if(cnfg)
      {
        Serial.println(msg);
      }
      if(msg.equals("S:DEVICE CONNECTED"))
      {
        dcon=true;
      }
      else if(msg.equals("S:ACCESS DENIED"))
      {
        dcon=false;
      }
      else if(msg.equals("S:REMOTE ONLINE"))
      {
        rcon=true;
      }
      else if(msg.equals("S:REMOTE OFFLINE")||msg.equals("S:REMOTE NOT CONNECTED"))
      {
        rcon=false;
      }
      else if(msg.equals("S:SERVER ONLINE"))
      {
        ping_chk=true;
      }
    }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if(event == WebsocketsEvent::ConnectionOpened)
    {
      wscon=true;
      if(cnfg)
      {
        Serial.println("S:SERVER ONLINE");
      }
      clnt.send(auth_key_str);
    }
    else if(event == WebsocketsEvent::ConnectionClosed)
    {
      wscon=false;
      if(cnfg)
      {
        Serial.println("S:SERVER OFFLINE");
      }
    }
}

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(128);
  initAddress();
  checkCode();
  checkActive();
  clnt.onMessage(onMessageCallback);
  clnt.onEvent(onEventsCallback);
  ws_link_str=loadWSLink();
  auth_key_str=loadAuthKey();
}

void loop()
{
  if(stat_actv)
  {
    wcon=(WiFi.status()==WL_CONNECTED);
    delay(500);
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

void initAddress()
{
  code=0;
  actv=1;
  base=2;
  wssid=base;
  wkey=wssid+20+1;
  wslink=wkey+30+1;
  authkey=wslink+50+1;
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
    clnt.send(a);
    return;
  }
  if(a.indexOf("D:")==0)
  {
    clnt.send(a.substring(2));
  }
  else if(a.equals("activate"))
  {
    ON();
    Serial.println("DEVICE ACTIVATED");
  }
  else if(a.equals("deactivate"))
  {
    OFF();
    Serial.println("DEVICE DEACTIVATED");
  }
  else if(a.indexOf("set#wifi:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
  {
    setWFID(a.substring(9,li));
    setKey(a.substring(li+1));
    Serial.println("WIFI SSID KEY UPDATED");
  }
  else if(a.equals("get#wifi"))
  {
    Serial.println("SSID :- "+loadWFID()+"### KEY :- "+loadKey());
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

void ON()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(loadWFID(),loadKey());
  setActive(true);
}

void OFF()
{
  WiFi.mode(WIFI_OFF);
  setActive(false);
}

void updateSnapTime()
{
  snp=millis();
}

void erase()
{
  OFF();
  setWFID("xyz");
  setKey("123456789");
  setAuthKey("IR1234567");
  setWSLink("ws://localhost:8080/");
}

void checkCode()
{
  if(getCode()!='W')
  {
    setCode();
  }
}

void checkActive()
{
  stat_actv=getActive();
  if(stat_actv)
  {
    ON();
  }
  else
  {
    OFF();
  }
}
//#############################################################################################
//code
void setCode()
{
  EEPROM.put(code,'W');
  EEPROM.commit();
  erase();
}

char getCode()
{
  char ccd;
  EEPROM.get(code,ccd);
  return ccd;
}

//actv
void setActive(boolean a)
{
  stat_actv=a;
  char actv_c;
  if(a)
  {
    actv_c='1';
  }
  else
  {
    actv_c='0';
  }
  EEPROM.put(actv,actv_c);
  EEPROM.commit();
}

boolean getActive()
{
  char actv_c;
  EEPROM.get(actv,actv_c);
  return (actv_c=='1');
}

//wifi id password
void setWFID(String a)
{
  int dlen=a.length();
  if(dlen>1&&dlen<=20)
  {
    writeString(wssid,a); 
  }
}

String loadWFID()
{
  return fetchString(wssid);
}

void setKey(String a)
{
  int dlen=a.length();
  if(dlen>=8&&dlen<=30)
  {
    writeString(wkey,a); 
  }
}

String loadKey()
{
  return fetchString(wkey);
}

//auth key

void setAuthKey(String a)
{
  int dlen=a.length();
  if(dlen=9)
  {
    writeString(authkey,a);
    auth_key_str=a;
  }
}

String loadAuthKey()
{
  return fetchString(authkey);
}

//wslink
void setWSLink(String a)
{
  int dlen=a.length();
  if(dlen>=10&&dlen<=50)
  {
    writeString(wslink,a);
    ws_link_str=a;
  }
}

String loadWSLink()
{
  return fetchString(wslink);
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
//#############################################################################################

void writeString(int a,String b)
{
  uint8_t alen=b.length();
  EEPROM.put(a,alen);
  for(int i=0;i<alen;i++)
  {
    char c=b.charAt(i);
    EEPROM.put(a+1+i,c);
  }
  EEPROM.commit();
}

String fetchString(int b)
{
  String tmp="";
  uint8_t alen;
  EEPROM.get(b,alen);
  for(int i=0;i<alen;i++)
  {
    char c;
    EEPROM.get(b+1+i,c);
    tmp+=c;
  }
  return tmp;
}

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

void initProcess();
void processHotspotFunction();
void toggleHotspot();
void ON();
void OFF();
void ON_AP();
void OFF_AP();
void confProcess();
void udpProcess();
void serialProcess();
void dataSend(String);
void sendTowardsHotspot(String);
void sendTowardsSerial(String);
void confCmd(String);
void erase();
void checkCode();
void checkActive();
void setCode();
char getCode();
void setActive(boolean);
boolean getActive();
void setWFID(String);
String loadWFID();
void setKey(String);
String loadKey();
void setServerIP(String);
String getServerIP();
void setServerPort(String);
String getServerPort();
void setAuthKey(String);
String loadAuthKey();
void writeString(int,String);
String fetchString(int);

IPAddress serv_ip;
uint16_t serv_port;
String auth_key_str;
boolean stat_actv;
int code,actv,base,wssid,wkey,iip,pport,authkey;

char symbol='U';

WiFiUDP udp_conf;
int push_button_pin=D3;
int led_pin=LED_BUILTIN;
boolean led_flg;
boolean hflg=true;
boolean tflg=true;
String ssid_ap="K";
String key_ap="123456789";
IPAddress rem_ip(192,168,4,255);
uint16_t rem_port=4210;

int conf=0;
int lst_msg=0;

void initProcess(boolean a)
{
  WiFi.mode(WIFI_AP_STA);
  udp_conf.begin(4210);
  code=0;
  actv=1;
  base=2;
  wssid=base;
  wkey=wssid+32+1;
  iip=wkey+64+1;
  pport=iip+15+1;
  authkey=pport+5+1;
  EEPROM.begin(150);
  checkCode();
  checkActive();
  serv_ip.fromString(getServerIP());
  serv_port=getServerPort().toInt();
  auth_key_str=loadAuthKey();
  led_flg=a;
  if(led_flg)
  {
    pinMode(led_pin,OUTPUT);
  }
  pinMode(push_button_pin,INPUT_PULLUP);
  digitalWrite(push_button_pin,HIGH);
  toggleHotspot();
}

void processHotspotFunction()
{
  boolean cflg=(digitalRead(push_button_pin)==HIGH);
  if(tflg==cflg)
  {
    return;
  }
  tflg=cflg;
  if(!tflg)
  {
   toggleHotspot();
   delay(1);
  }
}

void toggleHotspot()
{
  if(!hflg)
  {
    ON_AP();
    hflg=true;
  }
  else
  {
    OFF_AP();
    hflg=false;
  }
}

void ON()
{
  WiFi.begin(loadWFID(),loadKey());
  setActive(true);
}

void OFF()
{
  WiFi.disconnect();
  setActive(false);
}

void ON_AP()
{
  WiFi.softAP(ssid_ap,key_ap);
  if(led_flg)
  {
    digitalWrite(led_pin,LOW);
  }
}

void OFF_AP()
{
  WiFi.softAPdisconnect();
  if(led_flg)
  {
    digitalWrite(led_pin,HIGH);
  }
}

void confProcess()
{
  udpProcess();
  serialProcess();
}

void udpProcess()
{
  int cpi=udp_conf.parsePacket();
  if(cpi>0)
  {
    String a="";
    int rem_val;
    while((rem_val=udp_conf.read())>0)
    {
      a+=(char)(rem_val);
    }
    rem_ip=udp_conf.remoteIP();
    rem_port=udp_conf.remotePort();
    if(conf==0&&a.equals("H:config"))
    {
      conf=1;
      sendTowardsHotspot("H:ENTERED CONFIGURATION MODE");
    }
    else if(conf==1&&a.equals("H:exit"))
    {
      conf=0;
      sendTowardsHotspot("H:EXIT CONFIGURATION MODE");
    }
    else if(conf==1&&a.indexOf("H:")==0)
    {
      confCmd(a);
    }
  }
}

void serialProcess()
{
  if(Serial.available())
  {
    String a="";
    char c='\0';
    while(Serial.available())
    {
      c=(char)Serial.read();
      if(c=='\n'||c=='\r')
      {
        continue;
      }
      a+=c;
      delay(1);
    }
    if(conf==0&&a.equals("H:config"))
    {
      conf=2;
      sendTowardsSerial("H:ENTERED CONFIGURATION MODE");
    }
    else if(conf==2&&a.equals("H:exit"))
    {
      conf=0;
      sendTowardsSerial("H:EXIT CONFIGURATION MODE");
    }
    else if(conf==2&&a.indexOf("H:")==0)
    {
      confCmd(a);
    }
  }
}

void dataSend(String a)
{
  if(conf==1)
  {
    sendTowardsHotspot(a);
  }
  else if(conf==2)
  {
    sendTowardsSerial(a);
  }
}

void sendTowardsHotspot(String a)
{
  udp_conf.beginPacket(rem_ip,rem_port);
  for(int i=0;i<a.length();i++)
  {
    udp_conf.write((uint8_t)(a.charAt(i)));
  }
  udp_conf.endPacket();
}

void sendTowardsSerial(String a)
{
  Serial.println(a);
}

void confCmd(String a)
{
  if(a.equals("H:echo"))
  {
    dataSend("H:ECHO");
  }
  else if(a.equals("H:activate"))
  {
    ON();
    dataSend("H:DEVICE ACTIVATED");
  }
  else if(a.equals("H:deactivate"))
  {
    OFF();
    dataSend("H:DEVICE DEACTIVATED");
  }
  else if(a.indexOf("H:set#wifi_ssid:")==0)
  {
    setWFID(a.substring(16));
    dataSend("H:WIFI SSID UPDATED");
  }
  else if(a.indexOf("H:set#wifi_key:")==0)
  {
    setKey(a.substring(15));
    dataSend("H:WIFI SSID KEY UPDATED");
  }
  else if(a.equals("H:get#wifi_ssid"))
  {
    dataSend("H:wifi_ssid :- "+loadWFID());
  }
  else if(a.equals("H:get#wifi_key"))
  {
    String wfkey=loadKey();
    if(wfkey.equals(""))
    {
      wfkey="NULL";
    }
    dataSend("H:wifi_key :- "+wfkey);
  }
  else if(a.indexOf("H:set#serverip:")==0)
  {
    setServerIP(a.substring(15));
    dataSend("H:SERVER IP SET");
  }
  else if(a.equals("H:get#serverip"))
  {
    dataSend("H:Server IP :- "+getServerIP());
  }
  else if(a.indexOf("H:set#serverport:")==0)
  {
    setServerPort(a.substring(17));
    dataSend("H:SERVER PORT SET");
  }
  else if(a.equals("H:get#serverport"))
  {
    dataSend("H:Server Port :- "+getServerPort());
  }
  else if(a.indexOf("H:set#authkey:")==0)
  {
    setAuthKey(a.substring(14));
    dataSend("H:AUTHENTICATION KEY UPDATED");
  }
  else if(a.equals("H:get#authkey"))
  {
    dataSend("H:AUTHENTICATION KEY :- "+loadAuthKey());
  }
  else if(a.equals("H:erase"))
  {
    erase();
    dataSend("H:DEVICE SET TO DEFAULT");
  }
  else
  {
    dataSend("H:INVALID COMMAND");
  }
}

void erase()
{
  OFF();
  setWFID("xyz");
  setKey("123456789");
  setServerIP("192.168.43.1");
  setServerPort("4210");
  setAuthKey("TEST1234");
}

void checkCode()
{
  if(getCode()!=symbol)
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
//set get

//#############################################################################################
//code
void setCode()
{
  EEPROM.put(code,symbol);
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
  if(dlen>0&&dlen<=32)
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
  if(dlen==4&&a.equals("NULL"))
  {
    writeString(wkey,a);
  }
  else if(dlen>=8&&dlen<=64)
  {
    writeString(wkey,a); 
  }
}

String loadKey()
{
  String a=fetchString(wkey);
  if(a.equals("NULL"))
  {
    a="";
  }
  return a;
}

//server ip
void setServerIP(String a)
{
  IPAddress tmp;
  if(a.length()>=7&&tmp.fromString(a))
  {
    writeString(iip,a);
    serv_ip=tmp;
  }
}

String getServerIP()
{
  return fetchString(iip);
}
//server port
void setServerPort(String a)
{
  uint16_t tmp=a.toInt();
  if(tmp>=1024&&tmp<=65353)
  {
    writeString(pport,a);
    serv_port=tmp;
  }
}

String getServerPort()
{
  return fetchString(pport);
}
//auth key

void setAuthKey(String a)
{
  int dlen=a.length();
  if(dlen>=8&&dlen<=32)
  {
    writeString(authkey,a);
    auth_key_str=a;
  }
}

String loadAuthKey()
{
  return fetchString(authkey);
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

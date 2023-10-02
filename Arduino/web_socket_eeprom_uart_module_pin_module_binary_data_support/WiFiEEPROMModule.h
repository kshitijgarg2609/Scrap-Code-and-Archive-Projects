#include <EEPROM.h>
#include <ESP8266WiFi.h>

void initEEPROMProcess();
void initAddress();
void ON();
void OFF();
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
void setAuthKey(String);
String loadAuthKey();
void setWSLink(String);
String loadWSLink();
void writeString(int,String);
String fetchString(int);

String ws_link_str;
String auth_key_str;
boolean cnfg=false;
boolean stat_actv;
int code,actv,base,wssid,wkey,wslink,authkey;

void initEEPROMProcess()
{
  EEPROM.begin(128);
  initAddress();
  checkCode();
  checkActive();
  ws_link_str=loadWSLink();
  auth_key_str=loadAuthKey();
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
  if(dlen==4&&a.equals("NULL"))
  {
    writeString(wkey,a);
  }
  else if(dlen>=8&&dlen<=30)
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

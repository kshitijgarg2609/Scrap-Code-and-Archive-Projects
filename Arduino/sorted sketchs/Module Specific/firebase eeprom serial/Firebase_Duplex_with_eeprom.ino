#include <EEPROM.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

FirebaseData fdata;
FirebaseJson json;

int base=10;

boolean cnfg=false;
boolean wf=false;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  cnfg=getConfig();
  wf=getStat();
  if(wf)
  {
    ON();
  }
  else
  {
    OFF();
  }
}

void loop()
{
  Firebase.getInt(fdata,"/rx");
  if(fdata.intData()==1)
  {
    Firebase.getString(fdata,"/rxd");
    Serial.println(fdata.stringData());
    Firebase.setInt(fdata,"/rx",0);
  }
  delay(1);
  serialEvent();
}

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

void cmd(String a)
{
  int li;
  if(a.equals("config"))
  {
    setConfig(false);
    Serial.println("CONFIGURTION MODE ENTERED");
    return;
  }
  else if(a.equals("exit"))
  {
    setConfig(true);
    Serial.println("CONFIGURTION MODE EXIT");
    return;
  }
  
  if(cnfg)
  {
    sendToFirebase(a);
    return;
  }
  else if(a.indexOf("set#wifi:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
  {
    setID(a.substring(9,li));
    setKey(a.substring(li+1));
    Serial.println("WIFI SSID KEY UPDATED");
  }
  else if(a.equals("get#wifi"))
  {
    Serial.println("SSID :- "+loadID()+"   Key :- "+loadKey());
  }
  else if(a.indexOf("set#firebase:")!=-1&&(li=a.indexOf("@"))!=-1)
  {
    //setID(a.substring(7));
    //writeString(a.substring(7),2);
    setHost(a.substring(13,li));
    setAuth(a.substring(li+1));
    //Serial.println(a.substring(li+1));
    Serial.println("FIREBASE DATABASE AUTH HOST UPDATED");
  }
  else if(a.equals("get#firebase"))
  {
    Serial.println("Host :- "+loadHost()+"   Auth :- "+loadAuth());
  }
  else if(a.equals("on"))
  {
    ON();
    Serial.println("DEVICE ACTIVATED");
  }
  else if(a.equals("off"))
  {
    OFF();
    Serial.println("DEVICE DEACTIVATED");
  }
  else if(a.equals("reset#data"))
  {
    Firebase.setInt(fdata,"/rx",0);
    Firebase.setInt(fdata,"/tx",0);
    Firebase.setString(fdata,"/rxd","");
    Firebase.setString(fdata,"/txd","");
    Serial.println("FIREBASE DATABASE RESET");
  }
  else
  {
    Serial.println("INVALID COMMAND");
  }
}

void sendToFirebase(String a)
{
  
  Firebase.getInt(fdata,"/tx");
  //Serial.println("sending :- "+a);
  //Serial.println("test :- "+String(fdata.intData()));
  if(fdata.intData()==0)
  {
    //ftx.clear();
    Firebase.setString(fdata,"/txd",a);
    Firebase.setInt(fdata,"/tx",1);
    //ftx.clear();
    //ftx.clear();
  }
}

void ON()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(loadID(),loadKey());
  Firebase.begin(loadHost(),loadAuth());
  Firebase.reconnectWiFi(true);
  //Firebase.setReadTimeout(fdata,1000*60);
  //Firebase.setwriteSizeLimit(fdata,"tiny");
  setStat(true);
}

void OFF()
{
  WiFi.mode(WIFI_OFF);
  setStat(false);
}

void setConfig(boolean a)
{
  int add=0;
  byte v=a?1:0;
  EEPROM.put(add,v);
  cnfg=a;
  EEPROM.commit();
}

boolean getConfig()
{
  int add=0;
  byte v;
  EEPROM.get(add,v);
  return v==1;
}

void writeString(String a,int b)
{
  uint8_t alen=a.length();
  //Serial.println("Length :- "+String(alen));
  EEPROM.put(b,alen);
  for(int i=0;i<alen;i++)
  {
    char c=a.charAt(i);
    //Serial.println("Check :- "+String(b+1+i));
    EEPROM.put(b+1+i,c);
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

void setStat(boolean a)
{
  int add=base;
  byte v=a?1:0;
  EEPROM.put(add,v);
  wf=a;
}

boolean getStat()
{
  int add=base;
  byte v;
  EEPROM.get(add,v);
  return v==1;
}

void setID(String a)
{
  int dlen=a.length();
  if(dlen>0&&dlen<=18)
  {
    writeString(a,base+1); 
  }
}

String loadID()
{
  return fetchString(base+1);
}

void setKey(String a)
{
  int dlen=a.length();
  if(dlen>=8&&dlen<=19)
  {
    writeString(a,base+20); 
  }
}

String loadKey()
{
  return fetchString(base+20);
}

void setHost(String a)
{
  int dlen=a.length();
  if(dlen>=4&&dlen<=19)
  {
    writeString(a,base+40);
  }
}

String loadHost()
{
  return fetchString(base+40)+".firebaseio.com";
}

void setAuth(String a)
{
  int dlen=a.length();
  if(dlen==40)
  {
    writeString(a,base+60);
    //Serial.println("Auth entered : "+loadAuth());
  }
}

String loadAuth()
{
  return fetchString(base+60);
}

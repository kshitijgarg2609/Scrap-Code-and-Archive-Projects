#include <EEPROM.h>
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

//INFO STRING
String ws_link_str;
String auth_key_str;

//FLAGS
boolean cnfg=false;
boolean wcon=false;
boolean wscon=false;
boolean dcon=false;
boolean rcon=false;

//PROCESS CONTROL
boolean ping_flg=true;
boolean ping_chk=false;
long con_to=500;
long ping_send_to=10000;
long ping_rec_wait=2000;
long snp;

//ADDRESS
boolean stat_actv;
int code,actv,base,wssid,wkey,wslink,authkey;
int li;

//PIN DATA
String pin_name[10];
int pstor[10];
char pddr[10];
char pset[10];

using namespace websockets;
WebsocketsClient clnt;

void onMessageCallback(WebsocketsMessage message)
{
    String msg=message.data();
    if(msg.charAt(0)=='D')
    {
      if(msg.charAt(2)=='P'&&msg.charAt(3)==':')
      {
        pinControl(msg.substring(2));
      }
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
  initPinData();
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
void initPinData()
{
  int i;
  for(i=0;i<10;i++)
  {
    pddr[i]='X';
    pset[i]='X';
  }
  pstor[0]=D0;
  pstor[1]=D1;
  pstor[2]=D2;
  pstor[3]=D3;
  pstor[4]=D4;
  pstor[5]=D5;
  pstor[6]=D6;
  pstor[7]=D7;
  pstor[8]=D8;
  pstor[9]=A0;
  pin_name[0]="D0";
  pin_name[1]="D1";
  pin_name[2]="D2";
  pin_name[3]="D3";
  pin_name[4]="D4";
  pin_name[5]="D5";
  pin_name[6]="D6";
  pin_name[7]="D7";
  pin_name[8]="D8";
  pin_name[9]="A0";
}

void pinControl(String a)
{
  int len;
  int pnum;
  int indx;
  unsigned int pval;
  String pstr;
  len=a.length();
  if(len==3&&a.equals("P:#"))
  {
    pstr="P:#";
    for(pnum=0;pnum<10;pnum++)
    {
      pstr+=pddr[pnum];
    }
    pstr+="@";
    for(pnum=0;pnum<10;pnum++)
    {
      pstr+=pset[pnum];
    }
    clnt.send(pstr);
    return;
  }
  //pin selector
  if(a.charAt(2)=='D'&&(a.charAt(3)>='0'&&a.charAt(3)<='8'))
  {
    indx=a.charAt(3)-'0';
    pnum=pstor[indx];
  }
  else if(a.charAt(2)=='A'&&a.charAt(3)=='0')
  {
    indx=9;
    pnum=pstor[indx];
  }
  else
  {
    clnt.send("P:PIN INVALID");
    return;
  }
  if(len==4&&a.charAt(4)=='I')
  {
    pinMode(pnum,INPUT);
    pddr[indx]='I';
    clnt.send("P:"+pin_name[indx]+"SET TO INPUT");
  }
  else if(len==5&&a.charAt(4)=='O')
  {
    pinMode(pnum,OUTPUT);
    pddr[indx]='O';
    clnt.send("P:"+pin_name[indx]+"SET TO OUTPUT");
  }
  else if(len==5&&a.charAt(4)=='H')
  {
    digitalWrite(pnum,HIGH);
    pset[indx]='H';
    clnt.send("P:"+pin_name[indx]+"SET TO HIGH");
  }
  else if(len==5&&a.charAt(4)=='L')
  {
    digitalWrite(pnum,LOW);
    pset[indx]='L';
    clnt.send("P:"+pin_name[indx]+"SET TO LOW");
  }
  else if(len==8&&a.charAt(4)=='A')
  {
    pval=digit3(a.charAt(5),a.charAt(6),a.charAt(7));
    analogWrite(pnum,pval);
    pset[indx]='P';
    clnt.send("P:"+pin_name[indx]+"SET TO "+a.substring(5));
  }
  else if(len>5&&a.charAt(4)=='R')
  {
    if(len==6&&a.charAt(5)=='D')
    {
      pval=digitalRead(pnum);
      clnt.send("P:"+pin_name[indx]+((pval==HIGH)?":HIGH":":LOW"));
    }
    else if(len==6&&a.charAt(5)=='A')
    {
      pval=analogRead(pnum);
      clnt.send("P:"+pin_name[indx]+":"+zeroAppend(pval,(indx==9)?4:3));
    }
    else if(len>6&&a.charAt(5)=='P')
    {
      if(a.charAt(6)=='H')
      {
        if(len>=9&&a.charAt(7)=='T')
        {
          pval=pulseIn(pnum,HIGH,digitTime(a.substring(8)));
        }
        else
        {
          pval=pulseIn(pnum,HIGH);
        }
        clnt.send("P:"+pin_name[indx]+":"+String(pval));
      }
      else if(a.charAt(6)=='L')
      {
        if(len>=9&&a.charAt(7)=='T')
        {
          pval=pulseIn(pnum,LOW,digitTime(a.substring(8)));
        }
        else
        {
          pval=pulseIn(pnum,LOW);
        }
        clnt.send("P:"+pin_name[indx]+":"+String(pval));
      }
      else
      {
        clnt.send("P:INVALID PIN COMMAND");
      }
    }
  }
  else
  {
    clnt.send("P:INVALID PIN COMMAND");
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
String zeroAppend(int a,int b)
{
  String tmp="";
  int i;
  char c;
  for(i=1;i<=b;i++)
  {
    c=(char)((a%10)+'0');
    tmp=c+tmp;
    a/=10;
  }
  return tmp;
}

int digit2(char a,char b)
{
  return (((a-'0')*10)+(b-'0'));
}

int digit3(char a,char b,char c)
{
  return (((a-'0')*100)+((b-'0')*10)+(c-'0'));
}

unsigned long digitTime(String a)
{
  unsigned long sum=0;
  int tlen=a.length();
  int i;
  unsigned long multiplier=1;
  for(i=tlen-1;i>=0;i--)
  {
    sum+=(a.charAt(i)-'0')*multiplier;
    multiplier*=10;
  }
  return sum;
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

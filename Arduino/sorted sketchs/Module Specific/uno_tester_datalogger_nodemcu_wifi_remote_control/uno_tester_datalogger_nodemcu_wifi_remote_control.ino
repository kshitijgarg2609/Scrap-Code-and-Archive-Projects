#include <EEPROM.h>
//#include <FirebaseESP8266.h>
//#include <ESP8266WiFi.h>

//FirebaseData fdata;

boolean cnfg=false;
boolean wifi_state=false;
boolean logging=false;
//DataSet
String device_id="1234567890";
long ms=500;
//address
uint8_t program_check;
uint8_t conf;
uint8_t wf;
uint8_t lg;
int dvc;
int wssid;
int wkey;
int fdb;
int fkey;
int sec;

void setup()
{
  setupAddress();
  Serial.begin(115200);
  //EEPROM.begin(512);
  cnfg=getConfig();
  logging=getProcessStat();
  wifi_state=getStat();
  if(wifi_state)
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
}

void setupAddress()
{
  program_check=0;
  conf=1;
  wf=2;
  lg=3;
  dvc=4;
  wssid=1+dvc+10;
  wkey=1+wssid+30;
  fdb=1+wkey+30;
  fkey=1+fdb+30;
  sec=1+fkey+40;
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
  Serial.println(cmd(m));
}
//############################################################################
//Integrating function
String cmd(String a)
{
  int li;
  if(a.equals("config"))
  {
    setConfig(false);
    setProcessStat(false);
    return "CONFIGURTION MODE ENTERED";
  }
  else if(a.equals("exit"))
  {
    setConfig(true);
    return "CONFIGURTION MODE EXIT";
  }
  
  if(cnfg)
  {
    return "WORKING MODE";
  }
  else if(a.equals("start logging"))
  {
    setProcessStat(true);
    return "LOGGING ACTIVATED";
  }
  else if(a.equals("stop logging"))
  {
    setProcessStat(false);
    return "LOGGING DEACTIVATED";
  }
  else if(a.indexOf("set#device:")!=-1)
  {
    setDeviceID(a.substring(11));
    return "DEVICE ID SET";
  }
  else if(a.indexOf("get#device")!=-1)
  {
    return loadDeviceID();
  }
  else if(a.indexOf("set#wifi:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
  {
    setWFID(a.substring(9,li));
    setKey(a.substring(li+1));
    return "WIFI SSID KEY UPDATED";
  }
  else if(a.equals("get#wifi"))
  {
    return ("SSID :- "+loadWFID()+"   Key :- "+loadKey());
  }
  else if(a.indexOf("set#firebase:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
  {
    setHost(a.substring(13,li));
    setAuth(a.substring(li+1));
    return "FIREBASE DATABASE AUTH HOST UPDATED";
  }
  else if(a.equals("get#firebase"))
  {
    return ("Host :- "+loadHost()+"   Auth :- "+loadAuth());
  }
  else if(a.indexOf("set#interval:")!=-1)
  {
    setInterval(a.substring(13));
    return "INTERVAL SET";
  }
  else if(a.indexOf("get#interval")!=-1)
  {
    return loadInterval();
  }
  else if(a.equals("on"))
  {
    ON();
    return "DEVICE ACTIVATED";
  }
  else if(a.equals("off"))
  {
    OFF();
    return "DEVICE DEACTIVATED";
  }
  else if(a.equals("reset#data"))
  {
    /*
    Firebase.setInt(fdata,"/"+device_id+"/rx",0);
    Firebase.setInt(fdata,"/"+device_id+"/tx",0);
    Firebase.setString(fdata,"/"+device_id+"/rxd","");
    Firebase.setString(fdata,"/"+device_id+"/txd","");
    */
    return "FIREBASE DATABASE RESET";
  }
  else
  {
    return "INVALID COMMAND";
  }
}
//############################################################################
//Operation function
void ON()
{
  /*
  WiFi.mode(WIFI_STA);
  WiFi.begin(loadWFID(),loadKey());
  Firebase.begin(loadHost(),loadAuth());
  Firebase.reconnectWiFi(true);
  */
  setStat(true);
}

void OFF()
{
  //WiFi.mode(WIFI_OFF);
  setStat(false);
}
//############################################################################
//setter getter function EEPROM

//config######
//Program mark configuration
void programCheck()
{
  char prog_mark;
  EEPROM.get(program_check,prog_mark);
  if(prog_mark!='D')
  {
    erase();
  }
}

void erase()
{
  char prog_mark='D';
  setConfig(false);
  setStat(false);
  setProcessStat(false);
  setDeviceID("D123456789");
  setWFID("xyz");
  setKey("123456789");
  setHost("ABCD");
  setAuth("0123456789012345678901234567890123456789");
  setInterval("500");
  EEPROM.put(program_check,prog_mark);
}
//serial configuration mode
void setConfig(boolean a)
{
  byte v=a?1:0;
  EEPROM.put(conf,v);
  cnfg=a;
  //EEPROM.commit();
}

boolean getConfig()
{
  int add=0;
  byte v;
  EEPROM.get(conf,v);
  return v==1;
}

//wifi status
void setStat(boolean a)
{
  byte v=a?1:0;
  EEPROM.put(conf,v);
  wifi_state=a;
}

boolean getStat()
{
  byte v;
  EEPROM.get(conf,v);
  return v==1;
}

//logging status
void setProcessStat(boolean a)
{
  byte v=a?1:0;
  logging=a;
  EEPROM.put(lg,v);
}

boolean getProcessStat()
{
  byte v;
  EEPROM.get(lg,v);
  return v==1;
}

//main######
//device id
void setDeviceID(String a)
{
  int dlen=a.length();
  if(dlen>=5&&dlen<=10)
  {
    writeString(a,dvc); 
  }
}

String loadDeviceID()
{
  return fetchString(dvc);
}
//wifi id password
void setWFID(String a)
{
  int dlen=a.length();
  if(dlen>0&&dlen<=30)
  {
    writeString(a,wssid); 
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
    writeString(a,wkey); 
  }
}

String loadKey()
{
  return fetchString(wkey);
}
//firebase db_name auth key
void setHost(String a)
{
  int dlen=a.length();
  if(dlen>=4&&dlen<=20)
  {
    writeString(a,fdb);
    //Serial.println("host entered : "+loadHost());
  }
}

String loadHost()
{
  return fetchString(fdb)+".firebaseio.com";
}

void setAuth(String a)
{
  int dlen=a.length();
  if(dlen==40)
  {
    writeString(a,fkey);
  }
}

String loadAuth()
{
  return fetchString(fkey);
}
//seconds
void setInterval(String a)
{
  int dlen=a.length();
  if(dlen>=2)
  {
    long sum=0;
    long mul=1;
    for(int i=a.length()-1;i>=0;i--)
    {
      sum+=((a.charAt(i)-'0')*mul);
      mul*=10;
    }
    ms=sum;
    writeString(a,sec);
  }
}

String loadInterval()
{
  String a=fetchString(sec);
  long sum=0;
  long mul=1;
  for(int i=a.length()-1;i>=0;i--)
  {
    sum+=((a.charAt(i)-'0')*mul);
    mul*=10;
  }
  ms=sum;
  return a;
}

//############################################################################
//read write function EEPROM

void writeString(String a,int b)
{
  uint8_t alen=a.length();
  EEPROM.put(b,alen);
  for(int i=0;i<alen;i++)
  {
    char c=a.charAt(i);
    EEPROM.put(b+1+i,c);
  }
  //EEPROM.commit();
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

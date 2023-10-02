#include <EEPROM.h>

int base=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("EEPROM lENGTH :- "+EEPROM.length());
  EEPROM.begin(512);
}

void loop()
{
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
  //Serial.println(m);
  cmd(m);
}



void cmd(String a)
{
  int li;
  if(a.indexOf("set#id:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
  {
    //setID(a.substring(7));
    //writeString(a.substring(7),2);
    setID(a.substring(7,li));
    setKey(a.substring(li+1));
    //Serial.println(a.substring(li+1));
    Serial.println("WIFI SSID KEY UPDATED");
  }
  else if(a.equals("get#wifi"))
  {
    Serial.println("SSID :- "+loadID()+"   Key :- "+loadKey());
  }
  else if(a.indexOf("set#firebase:")!=-1&&(li=a.lastIndexOf("@"))!=-1)
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
}

void writeString(String a,int b)
{
  uint8_t alen=a.length();
  //Serial.println("Length :- "+String(alen));
  EEPROM.write(b,alen);
  for(int i=0;i<alen;i++)
  {
    char c=a.charAt(i);
    //Serial.println("Check :- "+String(b+1+i));
    EEPROM.write(b+1+i,c);
  }
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
  EEPROM.write(add,v);
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
  if(dlen>=10&&dlen<=19)
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
  }
}

String loadAuth()
{
  return fetchString(base+60);
}

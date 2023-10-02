#include <EEPROM.h>

int base_address=0;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  cmd("cmd");
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
  if(m=="")
  {
    return;
  }
  cmd(m);
}

void cmd(String m)
{
  if(m.equals("cmd"))
  {
    Serial.println("COMMANDS...");
    Serial.println("set:");
    Serial.println("get");
    Serial.println("erase");
  }
  else if(m.equals("get"))
  {
    Serial.println("String : "+fetchString());
  }
  else if(m.indexOf("set:")==0)
  {
    writeString(m.substring(4));
    Serial.println("STRING SET !!!");
  }
  else if(m.equals("erase"))
  {
    char c='\0';
    EEPROM.put(base_address,c);
    EEPROM.commit();
    Serial.println("ERASED STRING !!!");
  }
  else
  {
    Serial.println("INVALID COMMAND !!!");
  }
}

void writeString(String a)
{
  char c;
  for(int i=0;i<a.length();i++)
  {
    c=a.charAt(i);
    EEPROM.put(base_address+i,c);
  }
  c='\0';
  EEPROM.put(base_address+a.length(),c);
  EEPROM.commit();
}

String fetchString()
{
  String tmp="";
  for(int i=base_address;i<512;i++)
  {
    char c;
    EEPROM.get(i,c);
    if(c=='\0')
    {
      break;
    }
    tmp+=c;
  }
  return tmp;
}

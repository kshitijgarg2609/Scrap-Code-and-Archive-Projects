#include <EEPROM.h>

int add=200;
char flg='1';

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(flg=='1')
  {
    Serial.println(String(random(0,1024)));
    delay(20);
  }
}

void readStat()
{
  EEPROM.get(add,flg);
  if(flg!='0'&&flg!='1')
  {
    writeStat('0');
  }
}

void writeStat(char a)
{
  EEPROM.put(add,a);
  flg=a;
}

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(2);
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
   if(a.equals("start"))
   {
     writeStat('1');
   }
   else if(a.equals("stop"))
   {
     writeStat('0');
   }
}

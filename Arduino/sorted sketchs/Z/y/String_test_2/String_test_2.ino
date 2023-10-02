#include <EEPROM.h>

String m;
int n,i;
int l;

void setup()
{
  Serial.begin(9600);
  l=0;
  EEPROM.get(64,l);
}

void loop()
{
  m=rmsg();
  if(m!="")
  {
    delay(300);
    Serial.println("____________________________________________");
    Serial.println(m);
    l=m.length();
    for(i=0;i<m.length();i++)
    {
      n=m.charAt(i);
      Serial.println(n);
    }
    if(m=="GET"||m=="get")
    {
      l=EEPROM.get(64,l);
      Serial.println("Check length !!!");
      Serial.println(l);
    }
    else
    {
      EEPROM.put(64,l);
    }
    Serial.println("____________________________________________");
  }
}

String rmsg()
{
  m="";
  int l;
    if(Serial.available()>0)
    {
      m=Serial.readString();
      l=m.length();
      if(m.charAt(l-1)=='\n')
      {
        m=m.substring(0,l-1); 
      }
    }
   return m;
}

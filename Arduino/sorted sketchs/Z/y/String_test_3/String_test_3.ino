#include <EEPROM.h>

String m;
int n,i;
int l;
int val;

void setup()
{
  l=128;
  Serial.begin(9600);
}

void loop()
{
  m=rmsg();
  if(m!="")
  {
    if(m=="read")
    {
      n=0;
      m="";
      i=l;
      while(1)
      {
        EEPROM.get(i,val);
        if(val=='\n')
        {
          break;
        }
        else
        {
          i++;
          m=m+(char)(val);
        }
      }
      Serial.println(m);
    }
    else
    {
      n=0;
      for(i=l;i<(l+m.length());i++)
      {
        val=m.charAt(n);
        n++;
        EEPROM.put(i,val);   
      }
      val='\n';
      EEPROM.put(i,val);
    }
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

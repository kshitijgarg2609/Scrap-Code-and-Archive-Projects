#include "sensorset.h"

void setup()
{
  Serial.begin(115200);
  pinSet();
}

void loop()
{
  
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
  if(m!="")
  {
    cmd(m);
  }
}

void cmd(String a)
{
  if(a.equals("sensor"))
  {
    Serial.println("sensor#"+sensor());
  }
  else if(a.equals("led1:on"))
  {
    digitalWrite(led1_pin,HIGH);
    Serial.println("led1:on");
  }
  else if(a.equals("led1:off"))
  {
    digitalWrite(led1_pin,LOW);
    Serial.println("led1:off");
  }
  else if(a.equals("led2:on"))
  {
    digitalWrite(led2_pin,HIGH);
    Serial.println("led2:on");
  }
  else if(a.equals("led2:off"))
  {
    digitalWrite(led2_pin,LOW);
    Serial.println("led2:off");
  }
}

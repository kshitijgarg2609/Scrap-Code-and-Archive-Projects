#include <Servo.h>

Servo srv;

void setup()
{
  Serial.begin(115200);
  srv.attach(9,1000,2000);
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
  if(m=="")
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  srv.write(a.toInt());
  Serial.println(a);
}

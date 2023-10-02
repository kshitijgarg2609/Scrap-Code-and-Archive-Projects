#include <Servo.h>

Servo serv;

void setup()
{
  Serial.begin(115200);
  serv.attach(11,1000,2000);
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
  //serv.write((a.toInt()));
  serv.writeMicroseconds(a.toInt());
}

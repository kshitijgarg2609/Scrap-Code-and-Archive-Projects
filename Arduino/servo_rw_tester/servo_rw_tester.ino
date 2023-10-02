#include <Servo.h>

Servo s;
int pin=11;

void setup()
{
  Serial.begin(115200);
  s.attach(pin);
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
  cmd(m);
}

void cmd(String a)
{
  if(a.indexOf('w')==0)
  {
    s.write(a.substring(1).toInt());
  }
  else if(a.indexOf("wm")==0)
  {
    s.writeMicroseconds(a.substring(2).toInt());
  }
  else if(a.equals("r"))
  {
    Serial.println(String(s.read())+" degree");
  }
  else if(a.equals("rm"))
  {
    Serial.println(String(s.readMicroseconds())+" ms");
  }
  else
  {
    Serial.println("INVALID COMMAND");
  }
}

int digit3(char a,char b,char c)
{
  return (((a-'0')*100)+((b-'0')*10)+(c-'0'));
}

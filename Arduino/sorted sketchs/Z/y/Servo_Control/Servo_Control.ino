#include <Servo.h>

Servo sv;
String m;
int servo_pin=9;    //sevo pin
int pos=90;          //position of servo arm

void setup()
{
  Serial.begin(9600);
  sv.attach(servo_pin);
  sv.write(pos);
}

void loop()
{
  m="";
  m=rmsg();
  if(m!="")
  {
    Serial.println("tested !!!");
    cmd(m);
  }
}

String rmsg()
{
  m="";
  char c='\0';
    while(Serial.available()>0)
    {
      c=Serial.read();
      if(c=='\n')
      {
        break;
      }
      delay(2);
      m+=c;
    }
   return m;
}

int toNumber(String a)
{
  int x=1,i;
  char c;
  for(i=0;i<a.length();i++)
  {
    c=a.charAt(i);
    if(c<48||c>57)
    {
      return -1;
    }
  }
  return a.toInt();
}

void cmd(String a)
{
  int x,i,j;
  long rd;
  if(a.length()>4&&a.indexOf("mov ")==0)
  {
    x=toNumber(a.substring(4));
    if(x>=0&&x<=180)
    {
      pos=x;
      sv.write(x);
    }
  }
}

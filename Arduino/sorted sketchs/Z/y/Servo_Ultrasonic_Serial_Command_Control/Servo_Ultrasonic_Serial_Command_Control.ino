#include <Servo.h>

Servo sv;
String m;
int servo_pin=5;      //sevo pin
int echo=6;
int trig=7;
int pos=90;          //position of servo arm

float val;

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
    cmd(m);
  }
}

float readL()
{
  long duration,inches;
  float d;
  pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pinMode(echo,INPUT);
  duration=pulseIn(echo, HIGH);
  d=(float)(duration*0.017);
  return (d>=2&&d<400)?d:(-1);
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
  else if(a=="distance")
  {
    val=readL();
    Serial.println(val);
  }
  else
  {
    Serial.println("INVALID !!!");
  }
}

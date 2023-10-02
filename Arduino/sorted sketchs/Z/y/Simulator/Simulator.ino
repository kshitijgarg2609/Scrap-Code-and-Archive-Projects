#include <Servo.h>

Servo sv;

int servo=9;
int echo=6;
int trigger=7;

int pingflg=0;

String inst;

void setup()
{
  Serial.begin(9600);
  sv.attach(servo);
  sv.write(0);
}

void loop()
{
  inst=rmsg();
  if(inst!="")
  {
    commanddecode(inst);
  }
  if(pingflg==1)
  {
    pingdistance();
  }
  delay(10);
}

String rmsg()
{
  String str="";
  while(Serial.available()>0)
  {
    str+=char(Serial.read());
    delay(25);
  }
  Serial.flush();
  return str;
}

void commanddecode(String a)
{
  String cmd="";
  char c;
  int i;
  for(i=0;i<a.length();i++)
  {
    cmd+=uchar(a.charAt(i));
  }
  cmd=cmd.substring(0,3);
  if(cmd=="MOV"&&a.length()>4)
  {
    cmd=a.substring(4);
    if(a.charAt(3)==' '&&checknum(cmd)==1)
    {
      move(cmd.toInt());
    }
  }
  else if(cmd=="PNG")
  {
    pingflg=1;
    Serial.println("Starting ping Distance !");
  }
  else if(cmd=="STP")
  {
    pingflg=0;
    Serial.println("Stopping ping Distance !");
  }
  else
  {
    Serial.println("INVALID COMMAND !");
  }
}

int checknum(String a)
{
  a=a.substring(0,a.length()-1);
  int x=1,i;
  for(i=0;i<a.length();i++)
  {
    if(num(a.charAt(i))==0)
    {
      return 0;
    }
  }
  return 1;
}

int num(char a)
{
  return (a>=48&&a<57)?1:0;
}

char uchar(char a)
{
  return (a>=97&&a<=122)?(char)(a-32):a;
}

void move(int a)
{
  if(a>=0&&a<=180)
  {
    sv.write(a);
    Serial.println("Moved !");
  }
  else
  {
    Serial.println("INVALID MOVE !");
  }
}

void pingdistance()
{
  char buf[8];
  sprintf(buf,"%d cm",readL());
  Serial.println(buf);
}

int readL()
{ 
  long duration, inches, cm;
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  return (int)cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

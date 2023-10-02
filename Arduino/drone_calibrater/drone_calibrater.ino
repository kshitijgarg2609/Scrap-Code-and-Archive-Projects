#include <Servo.h>

int pin=9;

int spd=1000;
Servo serv;

void setup()
{
  Serial.begin(115200);
  serv.attach(pin,1000,2000);
  serv.write(1000);
  printMenu();
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
  if(a.equalsIgnoreCase("zero") || a.equalsIgnoreCase("z"))
  {
    setMotorSpeed(1000);
  }
  else if(a.equalsIgnoreCase("full") || a.equalsIgnoreCase("f"))
  {
    setMotorSpeed(2000);
  }
  else if(a.charAt(0)=='S' || a.charAt(0)=='s')
  {
    setMotorSpeed(a.substring(1).toInt());
  }
  else if(a.charAt(0)=='+')
  {
    if(a.length()==1)
    {
      addMotorSpeed(1);
    }
    else
    {
      addMotorSpeed(a.substring(1).toInt());
    }
  }
  else if(a.charAt(0)=='-')
  {
    if(a.length()==1)
    {
      subtractMotorSpeed(1);
    }
    else
    {
      subtractMotorSpeed(a.substring(1).toInt());
    }
  }
  else
  {
    printMenu();
  }
}

void printMenu()
{
  Serial.println("zero,z\nfull,f\nS<speed>,s<speed>\n+<speed>,+\n-<speed>,-");
}

void setMotorSpeed(int a)
{
  if(a<1000)
  {
    a=1000;
  }
  else if(a>2000)
  {
    a=2000;
  }
  serv.write(a);
  printMotorSpeed(a);
}

void printMotorSpeed(int a)
{
  spd=a;
  Serial.println("Current Motor Speed :- "+String(a));
}

void addMotorSpeed(int a)
{
  setMotorSpeed(spd+a);
}

void subtractMotorSpeed(int a)
{
  setMotorSpeed(spd-a);
}

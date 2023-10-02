#include <Servo.h>

String m;             //String input

Servo sv_1,sv_2,sv_3;
int start;
boolean a1,a2,a3;
int x1,x2,x3;          //position of servo arm

int motor,angle;

void setup()
{
  Serial.begin(9600);
  a1=false;
  a2=false;
  a3=false;
  start=0;
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

void activate(int m,int pos,int pin)
{
  if(m==1)
  {
    sv_1.attach(pin);
    sv_1.write(pos);
    a1=true;
  }
  if(m==2)
  {
    sv_2.attach(pin);
    sv_2.write(pos);
    a2=true;
  }
  else if(m==3)
  {
    sv_3.attach(pin);
    sv_3.write(pos);
    a3=true;
  }
}

void moveArm(int m,int pos)
{
  if(m==1&&a1)
  {
    sv_1.write(pos);
  }
  else if(m==2&&a2)
  {
    sv_2.write(pos);
  }
  else if(m==3&&a3)
  {
    sv_3.write(pos);
  }
  else
  {
    Serial.println("UNCONFIGURED PIN !!!");
  }
}

boolean separate(String a)
{
  if(a.length()>=3&&toNumber(a)!=-1&&a.indexOf('0')==1)
  {
    motor=toNumber(a.substring(0,1));
    angle=toNumber(a.substring(2));
    return ((motor==1)||(motor==2)||(motor==3))&&(angle>=0&&angle<=180);
  }
  else
  {
    return false;
  }
}

void invalid()
{
  Serial.println("INVALID COMMAND !!!");
}

void cmd(String a)
{
  int seg1,seg2,pinN;
  if(separate(a))
  {
    moveArm(motor,angle);
  }
  else if(a.length()>4&&a.indexOf("set")==0)
  {
    seg1=a.indexOf(' ');
    seg2=a.lastIndexOf('#');
    if(seg1!=-1&&seg2!=-1&&seg2<(a.length()-1)&&(seg2-seg1)>1)
    {
      pinN=toNumber(a.substring(seg2+1));
       if(pinN!=-1&&separate(a.substring(seg1+1,seg2)))
       {
         Serial.println("ACTIVATED !!!");
         activate(motor,angle,pinN);
       }
      else
      {
        invalid();
      }
    }
    else
    {
      invalid();
    }
  }
  else
  {
    invalid();
  }
}

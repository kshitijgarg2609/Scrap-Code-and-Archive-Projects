#include <Servo.h>

Servo sv;

int servo_pin=9;    //sevo pin
int pos=90;          //position of servo arm

int flg=0;          //flag for ping distance
int echo=6;         //echo pin
int trig=7;         //trigger pin
float val;          //current distance value

float park[3][6];

void setup()
{
  int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<6;j++)
    {
      park[i][j]=(float)(-1);
    }
  }
  Serial.begin(9600);
  sv.attach(servo_pin);
  sv.write(pos);
}

void loop()
{
  String rec;
  rec=rmsg();
  if(rec!="")
  {
    cmd(rec);
  }
  if(flg==1)
  {
    pingdistance();
  }
}

String rmsg()
{
  String rec="";  
  if(Serial.available()>0)
  {
  rec=Serial.readString();
  rec=rec.substring(0,rec.length()-1);
  }
  return rec; 
}

String UpperCase(String a)
{
  String ustr="";
  int i;
  char c;
  for(i=0;i<a.length();i++)
  {
    c=a.charAt(i);
    ustr+=(c>=97&&c<=122)?(char)(c-32):c;
  }
  return ustr;
}

void cmd(String a)
{
  int x,i,j;
  a=UpperCase(a);
  //MOV
  if(a.length()>4&&a.indexOf("MOV ")==0)
  {
    x=toNumber(a.substring(4));
    if(x>=0&&x<=180)
    {
      pos=x;
      sv.write(x);
      Serial.println("Moved!");
    }
    else
    {
      invalid();
    }
  }
  //PING
  else if(a.indexOf("PING")==0)
  {
    flg=1;
    Serial.println("Starting ping Distance !");
  }
  //STOP
  else if(a.indexOf("STOP")==0)
  {
    flg=0;
    Serial.println("Stopping ping Distance !");
  }
  //SET
  else if(a.length()>4&&a.indexOf("SET ")==0)
  {
    if(flg==1)
    {
      x=toNumber(a.substring(4));
      x=check(x);
      if(x==-1)
      {
        Serial.println("ENTER A VALID SLOT !");
        return;
      }
      i=x/10;   //slot number
      j=x%10;   //bound number
      park[0][i-1]=(float)pos;
      park[j][i-1]=val;
      flg=0;
      Serial.println("VALUE IS SET !");
      delay(300);
    }
    else
    {
      Serial.println("ENABLE PING DISTANCE FIRST !");
    }
  }
  else if(a.indexOf("SHOW")==0)
  {
    Serial.println("____________________________________________________________________________");
    for(i=0;i<3;i++)
    {
      //if()
      //Serial.println();
      for(j=0;j<6;j++)
      {
        Serial.print(park[i][j]);
        Serial.print("\t\t");
      }
      Serial.println();
    }
    Serial.println("____________________________________________________________________________");
  }
  else if(a.indexOf("EXP")==0)
  {
  }
  else if(a.indexOf("HLT")==0)
  {
  }
  else
  {
    invalid();
  }
}

void invalid()
{
  Serial.println("INVALID COMMAND !");
}

int check(int a)
{
  if(a==11||a==12||a==21||a==22||a==31||a==32||a==42||a==42||a==52||a==52||a==62||a==62)
  {
    return a;
  }
  return -1;
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

float readL()
{
long duration, inches;
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
pinMode(echo, INPUT);
duration = pulseIn(echo, HIGH);
return (float)(duration*0.017);
}

void pingdistance()
{
  val=readL();
  Serial.println(val);
  delay(100);
}

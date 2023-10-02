#include <EEPROM.h>

int trigA=8;
int echoA=9;
int trigB=10;
int echoB=11;

int rng;

float lvA=0;
float lvB=0;

boolean infA=false;
boolean infB=false;

boolean queue=false;

char spd;

void setup()
{
  pinMode(trigA,OUTPUT);
  pinMode(echoA,INPUT);
  pinMode(trigB,OUTPUT);
  pinMode(echoB,INPUT);
  Serial.begin(115200);
  loadFromRom();
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
  //Serial.println(m);
  cmd(m);
}

void cmd(String a)
{
  if(a.indexOf("set range=")!=-1)
  {
    a=a.substring(a.lastIndexOf('=')+1);
    saveToRom(a.toInt());
    loadFromRom();
    Serial.println(rng);
  }
  else if(a.equals("range"))
  {
    Serial.println(rng);
  }
  else if(a.equals("distance"))
  {
    Serial.println(String(readA())+":"+String(readB()));
  }
  else if(a.equals("distance:a"))
  {
    Serial.println(String(readA()));
  }
  else if(a.equals("distance:b"))
  {
    Serial.println(String(readB()));
  }
  else
  {
    Serial.println(a);
  }
}

void saveToRom(int x)
{
  char fbit='V';
  if(x>=2&&x<=400)
  {
    EEPROM.put(16,fbit);
    fbit=(x%10)+48;
    x/=10;
    EEPROM.put(19,fbit);
    fbit=(x%10)+48;
    x/=10;
    EEPROM.put(18,fbit);
    fbit=(x%10)+48;
    x/=10;
    EEPROM.put(17,fbit);
  }
}

void loadFromRom()
{
  int x=0;
  char fbit;
  EEPROM.get(16,fbit);
  if(fbit!='V')
  {
    saveToRom(10);
  }
  EEPROM.get(17,fbit);
  x+=(fbit-48)*100;
  EEPROM.get(18,fbit);
  x+=(fbit-48)*10;
  EEPROM.get(19,fbit);
  x+=(fbit-48);
  if(!(x>=3&&x<=400))
  {
    saveToRom(10);
    rng=10;
  }
  else
  {
    rng=x;
  }
}

float readA()
{
  float dist;
  long duration;
  digitalWrite(trigA,LOW);
  delayMicroseconds(2);
  digitalWrite(trigA,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA,LOW);
  duration=pulseIn(echoA,HIGH);
  dist=duration*0.017;
  return (dist>=2&&dist<=rng)?dist:(-1);
}

float readB()
{
  float dist;
  long duration;
  digitalWrite(trigB,LOW);
  delayMicroseconds(2);
  digitalWrite(trigB,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB,LOW);
  duration = pulseIn(echoB,HIGH);
  dist=duration*0.017;
  return (dist>=2&&dist<=rng)?dist:(-1);
}

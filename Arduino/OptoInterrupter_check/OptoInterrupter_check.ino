#include <Servo.h>

//pins
int spdr=11;
int opto=2;
int brake=6;

Servo serv;

long cnt=0;
long rot=0;

//long r=0;
//boolean rnd=false;
long r_count=0;
boolean round_flg=false;
boolean high_flg=false;
boolean sensor_flg=false;

//
boolean brake_flg=false;
long brake_snp;

void setup()
{
  Serial.begin(115200);
  pinMode(opto,INPUT);
  pinMode(spdr,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  analogWrite(spdr,0);
  serv.attach(brake);
  serv.write(180);
  attachInterrupt(digitalPinToInterrupt(opto),processHighLow,CHANGE);
  resetCnt();
}

void loop()
{
  if(brake_flg&&((millis()-brake_snp)>=2000))
  {
    serv.write(180);
    brake_flg=false;
  }
}

void processHighLow()
{
  if(high_flg&&digitalRead(opto)==HIGH)
  {
    counter();
    if(round_flg&&(cnt>=r_count))
    {
      cmd("S000");
      cmd("BRAKE");
      round_flg=false;
    }
    high_flg=false;
  }
  if(!high_flg&&digitalRead(opto)==LOW)
  {
    high_flg=true;
  }
}

void counter()
{
  cnt++;
  //timeUpdate();
  if((cnt%8)==0)
  {
    rot++;
    Serial.println("TOTAL ROTATIONS :- "+String(rot));
  }
  else
  {
    Serial.println("COUNT :- "+String(cnt));
  }
  
  //Serial.println("COUNT :- "+String(cnt));
}
/*
void timeUpdate()
{
  snp=millis();
  oflg=true;
}
*/
void resetCnt()
{
  cnt=0;
  rot=0;
  r_count=0;
}


void cmd(String a)
{
  int spd;
  if(a.length()==4&&a.charAt(0)=='S')
  {
    spd=digit3(a.charAt(1),a.charAt(2),a.charAt(3));
    analogWrite(spdr,spd);
    Serial.println("SPEED CHANGED");
  }
  else if(a.length()==4&&a.charAt(0)=='R')
  {
    resetCnt();
    r_count=digit3(a.charAt(1),a.charAt(2),a.charAt(3));
    r_count*=8;
    Serial.println("Check : "+String(r_count));
    round_flg=true;
    analogWrite(spdr,150);
  }
  else if(a.length()==9&&a.charAt(0)=='O'&&a.charAt(1)=='R'&&a.charAt(5)=='S')
  {
    resetCnt();
    r_count=digit3(a.charAt(2),a.charAt(3),a.charAt(4));
    spd=digit3(a.charAt(6),a.charAt(7),a.charAt(8));
    analogWrite(spdr,spd);
    r_count*=8;
    round_flg=true;
  }
  else if(a.length()==3&&a.equals("RST"))
  {
    resetCnt();
    analogWrite(spdr,0);
  }
  else if(a.length()==5&&a.equals("BRAKE"))
  {
    brake_snp=millis();
    serv.write(90);
    brake_flg=true;
  }
  else
  {
    Serial.println("INVALID COMMAND");
  }
  
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

int digit3(char a,char b,char c)
{
  return (((a-'0')*100)+((b-'0')*10)+(c-'0'));
}

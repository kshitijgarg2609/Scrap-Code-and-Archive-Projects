#include <Servo.h>

Servo lid;

boolean lid_flg=true;

int trig1=D1;
int echo1=D2;
int trig2=D6;
int echo2=D5;

void setup()
{
  Serial.begin(115200);
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  lid.attach(D7);
  closeLid();
}

void loop()
{
  float lid_dist=readUltrasonic(trig1,echo1);
  Serial.println(String(lid_dist));
  if(lid_dist>10)
  {
    closeLid();
  }
  else if(lid_dist>=2.5&&lid_dist<=9.5)
  {
    openLid();
  }
}

float readUltrasonic(int trig,int echo)
{
  float dis;
  long duration;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseInLong(echo,HIGH);
  dis=duration*0.017;
  dis=(dis>=2&&dis<=200)?dis:(-1);
  return dis;
}

void closeLid()
{
  if(!lid_flg)
  {
    return;
  }
  lid.write(0);
  lid_flg=false;
}

void openLid()
{
  if(lid_flg)
  {
    return;
  }
  lid.write(90);
  lid_flg=true;
}

#include <Servo.h>

int serv=5;
int echo=6;
int trig=7;

Servo sv;
int pos=90;
double val;

void setup()
{
  sv.attach(serv);
  sv.write(90);
}

void loop()
{
  delay(50);
  val=readL();
  if(val>=2&&val<=10)
  {
    openD();
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

void openD()
{
  while(pos!=30)
  {
    delay(10);
    pos--;
    sv.write(pos);
  }
  delay(2000);
  closeD();
}

void closeD()
{
  while(pos!=90)
  {
    delay(10);
    pos++;
    sv.write(pos);
  }
}

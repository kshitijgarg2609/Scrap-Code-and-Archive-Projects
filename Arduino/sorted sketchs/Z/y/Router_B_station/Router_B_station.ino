#include <Servo.h>

Servo sv;

//int i=50;

boolean op=false;

void setup()
{
  //pinMode(4,INPUT);//door
  attachInterrupt(digitalPinToInterrupt(2),access,CHANGE);
  pinMode(7,INPUT);//fan
  pinMode(8,OUTPUT);//fan connected
  pinMode(9,OUTPUT);
  //pinMode(10,OUTPUT);
  //canalogWrite(10,50);
  sv.attach(10);//servo
  sv.write(90);
}

void loop()
{
  /*
  //servo
  if(digitalRead(4)==HIGH)
  {
    for(;i>=50;i-=10)
    {
    analogWrite(10,i);
    //sv.write(180);
    delay(10);
    }
    
  }
  else
  {
    for(;i<=250;i+=10)
    {
      analogWrite(10,i);
       delay(10);
    }
    //sv.write(90);
  }
  */
  //dc
  if(digitalRead(7)==HIGH)
  {
    digitalWrite(8,HIGH);
    analogWrite(9,255);
  }
  else
  {
    digitalWrite(8,LOW);
    analogWrite(9,0);
  }
}

void access()
{
  if(op)
  {
    sv.write(180);
    op=false;
  }
  else
  {
    sv.write(90);
    op=true;
  }
}

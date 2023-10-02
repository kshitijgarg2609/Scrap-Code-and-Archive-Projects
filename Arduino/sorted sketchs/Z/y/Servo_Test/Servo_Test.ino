#include <Servo.h>  
#include <string.h>

Servo sv;

int p=0;
int t=0;

void setup()
{
  sv.attach(9);
}
void loop()
{
  p=p+3;
  if(p>180)
  {
    p=p%181;
  }
  if(t==1)
  {
    t=0;
    sv.write(p);
  }
  else if(t==0)
  {
    t=1;
    sv.write(180-p);
  }
  delay(150);
}

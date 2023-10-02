int a=00;
int b=00;
int c=00;
int d=00;
int e=00;
int f=00;

void setup()
{
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
 

void loop()
{
  analogWrite(3,a);
  analogWrite(5,b);
  analogWrite(6,c);
  analogWrite(9,d);
  analogWrite(10,e);
  analogWrite(11,f);
  a=(a+1)%256;
  b=(b+1)%256;
  c=(c+1)%256;
  d=(d+1)%256;
  e=(e+1)%256;
  f=(f+1)%256;
  delay(10);
}

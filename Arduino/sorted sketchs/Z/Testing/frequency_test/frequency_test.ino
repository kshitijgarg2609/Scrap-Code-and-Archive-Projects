float f,r;

int p=3;

void setup()
{
  Serial.begin(9600);
  pinMode(p,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),measure,LOW);
}

void loop()
{
}

void measure()
{
  f=pulseIn(p,HIGH,400);//pulseIn(p,LOW,400);
  if(f!=0)
  {
    f=1000000.0/f;
  }
  r=f/7.5;
  Serial.println(r);
}

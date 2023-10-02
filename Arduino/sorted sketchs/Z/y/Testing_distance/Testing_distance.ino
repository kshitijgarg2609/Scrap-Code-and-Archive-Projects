int trig=7;
int echo=6;

void setup()
{
Serial.begin(9600);
}

void loop()
{
pingdistance();
delay(350);
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
  char buf[14];
  float val=readL();
  //sprintf(buf,"%f cm",val);
  Serial.println(val);
  delay(100);
}

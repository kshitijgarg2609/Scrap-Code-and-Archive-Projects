int trigA=11;
int echoA=12;
int trigB=3;
int echoB=4;
int buzzer=6;

void setup()
{
  pinMode(trigA,OUTPUT);
  pinMode(echoA,INPUT);
  pinMode(trigB,OUTPUT);
  pinMode(echoB,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  Serial.println(String(readA())+":"+String(readB()));
  delay(200);
  digitalWrite(buzzer,HIGH);
  delay(200);
  digitalWrite(buzzer,LOW);
  delay(200);
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
  return (dist>=2&&dist<=300)?dist:(-1);
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
  return (dist>=2&&dist<=300)?dist:(-1);
}

int trig=12;
int echo=13;
float val;
float t;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  t=millis();
  val=readL();
  t=millis()-t;
  Serial.println(val);
  Serial.println(("Time Taken :- "+String(t)));
  delay(100);
}

float readL()
{
  float dist;
  long duration, inches;
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  dist=duration*0.017;
  //return dist;
  return (dist>=2&&dist<=400)?dist:(-1);
}

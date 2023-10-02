int trig=12;
int echo=13;
float val;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val=readL();
  Serial.println(val);
  delay(200);
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
  dist=(float)(duration*0.017);
  return (dist>=2&&dist<=400)?dist:(-1);
}

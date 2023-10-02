int pin1=14;
int pin2=2;

void setup()
{
  //pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
}

void loop()
{
  //digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  delay(750);
  //digitalWrite(pin1,LOW);
  digitalWrite(pin2,LOW);
  delay(750);
}

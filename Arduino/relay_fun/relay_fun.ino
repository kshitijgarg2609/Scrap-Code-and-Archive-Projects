void setup()
{
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
}

void loop()
{
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  delay(4000);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,LOW);
  delay(1000);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  delay(4000);
  digitalWrite(D5,LOW);
  digitalWrite(D6,HIGH);
  delay(1000);
}

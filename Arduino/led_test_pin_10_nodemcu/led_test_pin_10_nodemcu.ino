int pin=D5;

void setup()
{
  pinMode(pin,OUTPUT);
}

void loop()
{
  digitalWrite(pin,HIGH);
  delay(500);
  digitalWrite(pin,LOW);
  delay(500);
}

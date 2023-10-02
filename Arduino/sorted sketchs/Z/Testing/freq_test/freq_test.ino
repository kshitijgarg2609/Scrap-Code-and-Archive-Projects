void setup()
{
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop()
{
  Serial.println((pulseIn(2,HIGH)+pulseIn(2,LOW))/2);
  delay(100);
}

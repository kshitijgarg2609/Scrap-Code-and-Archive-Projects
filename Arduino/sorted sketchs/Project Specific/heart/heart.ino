void setup()
{
  Serial.begin(9600);
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
}

void loop()
{
  if(digitalRead(D0)==LOW&&digitalRead(D1)==LOW)
  {
    Serial.println(analogRead(A0));
  }
  delay(1);
}

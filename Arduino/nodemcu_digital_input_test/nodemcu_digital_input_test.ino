void setup()
{
  Serial.begin(115200);
  pinMode(D5,INPUT_PULLUP);
  digitalWrite(D5,HIGH);
}

void loop()
{
  if(digitalRead(D5)==HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }
  delay(500);
}

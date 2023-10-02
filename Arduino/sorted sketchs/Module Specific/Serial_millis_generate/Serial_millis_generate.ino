void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(String(millis()));
  delay(500);
}

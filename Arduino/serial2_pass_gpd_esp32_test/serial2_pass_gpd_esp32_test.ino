void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop()
{
  if(Serial2.available())
  {
    Serial.write(Serial2.read());
  }
}

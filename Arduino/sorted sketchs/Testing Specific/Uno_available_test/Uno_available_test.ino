void setup()
{
  Serial.begin(9600);
}

void loop()
{
}

void serialEvent()
{
  Serial.println(String(Serial.available()));
}

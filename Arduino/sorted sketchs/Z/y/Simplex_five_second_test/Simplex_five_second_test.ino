void setup()
{
  Serial.begin(9600);
}

void loop()
{
  delay(2000);
  Serial.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

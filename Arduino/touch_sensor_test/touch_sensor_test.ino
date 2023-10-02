void setup()
{
  Serial.begin(115200);
  pinMode(D2,INPUT);
}

void loop()
{
  Serial.printf("%d\n",digitalRead(D2));
}

int pin=25;
void setup()
{
  Serial.begin(115200);
  pinMode(pin,INPUT_PULLUP);
}

void loop()
{
  Serial.println(digitalRead(pin));
}


int pin=A0;
int adc=0;
float volt;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  adc=analogRead(pin);
  //volt=((adc*5.0)/1024.0);
  Serial.println("ADC : "+String(adc));
  delay(500);
}

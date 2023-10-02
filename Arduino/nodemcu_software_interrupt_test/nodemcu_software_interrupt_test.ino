int pin=D3;

boolean flg=true;

void setup()
{
  Serial.begin(115200);
  pinMode(pin,INPUT_PULLUP);
  digitalWrite(pin,HIGH);
}

void loop()
{
  interruptFunction();
}

void interruptFunction()
{
  boolean cflg=(digitalRead(pin)==LOW);
  if(flg==cflg)
  {
    return;
  }
  flg=cflg;
  if(flg)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }
}

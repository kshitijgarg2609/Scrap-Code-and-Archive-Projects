int pin=D3;
int led=D4;
boolean flg=true;
boolean led_flg=false;

void setup()
{
  Serial.begin(115200);
  pinMode(pin,INPUT_PULLUP);
  pinMode(led,OUTPUT);
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
    toggleLed();
  }
}

void toggleLed()
{
  led_flg=!led_flg;
  if(led_flg)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
}

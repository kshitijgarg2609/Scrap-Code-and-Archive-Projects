boolean flg=true;
int pin=D5;

void setup()
{
  Serial.begin(115200);
  pinMode(pin,INPUT_PULLUP);
  digitalWrite(pin,HIGH);
  attachInterrupt(digitalPinToInterrupt(pin),operateAP,HIGH);
}

void operateAP()
{
  if(flg)
  {
    Serial.println("1");
    flg=false;
  }
  else
  {
    Serial.println("2");
    flg=true;
  }
}

void loop()
{
  
}

int pin_led1=4;
int pin_led2=5;
int pin_button=6;

boolean flg=true;
long snp=millis();
long interval=1000;
boolean blink_flg=true;

void setup()
{
  pinMode(pin_led1,OUTPUT);
  pinMode(pin_led2,OUTPUT);
  pinMode(pin_button,INPUT_PULLUP);
}

void loop()
{
  if((millis()-snp)>=interval)
  {
    if(blink_flg)
    {
      digitalWrite(pin_led1,HIGH);
      blink_flg=false;
    }
    else
    {
      digitalWrite(pin_led1,LOW);
      blink_flg=true;
    }
  }
  if(flg && digitalRead(pin_button)==LOW)
  {
    digitalWrite(pin_led2,HIGH);
    if(interval==1000)
    {
      interval=500;
    }
    else
    {
      interval=1000;
    }
    flg=false;
  }
  if(!flg && digitalRead(pin_button)==HIGH)
  {
    digitalWrite(pin_led2,LOW);
    flg=true;
  }
}

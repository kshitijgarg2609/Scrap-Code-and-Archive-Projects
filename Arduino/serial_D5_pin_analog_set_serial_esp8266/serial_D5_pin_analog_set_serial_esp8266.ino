int pin=D0;

void setup()
{
  pinMode(D5,OUTPUT);
  Serial.begin(115200);
  cmd("0");
}

void loop()
{
  serialEvent();
}

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  if(m.equals(""))
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  uint16_t spd = (uint16_t)(a.toInt());
  analogWrite(pin,spd);
  Serial.println("Speed Set To :- "+String(spd));
}

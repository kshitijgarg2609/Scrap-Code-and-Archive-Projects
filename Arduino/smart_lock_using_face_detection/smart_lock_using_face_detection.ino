int lock_pin=13;

void setup() 
{
  pinMode(lock_pin,OUTPUT);
  triggerLock(false);
  Serial.begin(115200);
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
  if(m=="")
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  int i=a.toInt();
  if(i==0)
  {
    triggerLock(false);
  }
  else
  {
    triggerLock(true);
  }
}

void triggerLock(boolean a)
{
  if(a)
  {
    digitalWrite(lock_pin,HIGH);
  }
  else
  {
    digitalWrite(lock_pin,LOW);
  }
}

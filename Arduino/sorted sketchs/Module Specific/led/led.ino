void setup()
{
  Serial.begin(115200);
  pinMode(2,OUTPUT);
}

void loop()
{
  
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
  //Serial.println(m);
  if(m=="")
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  if(a.equals("ON"))
  {
    digitalWrite(2,HIGH);
  }
  else if(a.equals("OFF"))
  {
    digitalWrite(2,LOW);
  }
}

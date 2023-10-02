void setup()
{
  Serial.begin(115200);
}

void loop()
{
  serialEvent();
}

void serialEvent()
{
  int i=0;
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    if(i%10==0)
    {
      delay(1);
      i/=10;
    }
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
    i++;
  }
  if(m=="")
  {
    return;
  }
  Serial.println(m);
  //Serial.flush();
}

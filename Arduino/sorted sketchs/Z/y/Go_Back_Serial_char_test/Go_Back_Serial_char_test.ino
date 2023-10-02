String m;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  m=rmsg();
  if(m!="")
  {
    Serial.println(m);
  }
}

String rmsg()
{
  m="";
  char c='\0';
    while(Serial.available()>0)
    {
      c=Serial.read();
      if(c=='\n')
      {
        break;
      }
      delay(2);
      m+=c;
    }
   return m;
}

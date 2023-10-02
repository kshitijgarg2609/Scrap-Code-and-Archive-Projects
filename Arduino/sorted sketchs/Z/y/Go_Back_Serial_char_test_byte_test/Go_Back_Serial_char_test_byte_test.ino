String m;
int xyz;

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
    Serial.println("Test bytes");
    for(char c:m)
    {
      xyz=c;
      Serial.println(xyz);
    }
  }
}

String rmsg()
{
  m="";
  char c='\0';
    while(Serial.available()>0)
    {
      if(c=='\n')
      {
        break;
      }
      c=Serial.read();
      m+=c;
      delay(1);
    }
    Serial.flush();
   return m;
}

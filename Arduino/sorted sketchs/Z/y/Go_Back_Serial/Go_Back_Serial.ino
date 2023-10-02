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
  int l;
    if(Serial.available()>0)
    {
      m=Serial.readString();
      l=m.length();
      if(m.charAt(l-1)=='\n')
      {
        m=m.substring(0,l-1); 
      }
    }
   return m;
}

String m;
int n,i;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  m=rmsg();
  if(m!="")
  {
    delay(300);
    Serial.println("____________________________________________");
    Serial.println(m);
    for(i=0;i<m.length();i++)
    {
      n=m.charAt(i);
      Serial.println(n);
    }
    Serial.println("____________________________________________");
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

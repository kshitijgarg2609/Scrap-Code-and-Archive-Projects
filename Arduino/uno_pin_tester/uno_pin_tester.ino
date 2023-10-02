/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

void setup()
{
  Serial.begin(115200);
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
  if(m=="")
  {
    return;
  }
  cmd(m);
}

void cmd(String a)
{
  int pnum;
  if(a.indexOf("P")==0)
  {
    //pnum=((a.charAt(2)-'0')*10)+(a.charAt(3)-'0');
    if(a.charAt(4)=='I')
    {
      Serial.println("INVALID PIN NUMBER");
      return;
    }
    if(a.charAt(4)=='I')
    {
      pinMode(pnum,INPUT);
    }
    else if(a.charAt(4)=='O')
    {
      pinMode(pnum,OUTPUT);
    }
    else if(a.charAt(4)=='H')
    {
      digitalWrite(pnum,HIGH);
    }
    else if(a.charAt(4)=='L')
    {
      digitalWrite(pnum,LOW);
    }
  }
}

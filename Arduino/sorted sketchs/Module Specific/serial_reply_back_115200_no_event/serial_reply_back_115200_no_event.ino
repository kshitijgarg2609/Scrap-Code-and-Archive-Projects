void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if(Serial.available())
  {
    String msg="";
    while(Serial.available())
    {
      char c=Serial.read();
      if(c=='\n'||c=='\r')
      {
        continue;
      }
      delay(1);
      msg=msg+c;
    }
    Serial.println(msg);
  }
}

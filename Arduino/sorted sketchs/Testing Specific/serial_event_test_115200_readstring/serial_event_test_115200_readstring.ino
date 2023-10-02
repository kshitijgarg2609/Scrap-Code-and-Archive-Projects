char arr[10];

void setup()
{
  Serial.begin(115200);
}

void loop()
{
}

void serialEvent()
{
  int i,j;
  String m="";
  //Serial.flush();
  while(Serial.available())
  {
    delay(1);
    i=Serial.readBytesUntil('\n',arr,10);
    if(i>0)
    {
      for(j=0;j<i;j++)
      {
        m+=arr[j];
      }
    }
  }
  Serial.println(m);
  //Serial.flush();
  //Serial.println("UNO");
  //Serial.println("8mhz");
}

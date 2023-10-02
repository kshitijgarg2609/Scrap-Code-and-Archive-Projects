#include <DHT.h>

int pin=12;
String m;
float val;

DHT dht(12,DHT11);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  m=rmsg();
  if(m!="")
  {
    if(m.indexOf('h')!=-1)
    {
      val=dht.readHumidity();
      if(isnan(val))
      {
        val=-1;
      }
      Serial.println(val);
    }
    else if(m.indexOf('t')!=-1)
    {
      val=dht.readTemperature();
      if(isnan(val))
      {
        val=-1;
      }
      Serial.println(val);
    }
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

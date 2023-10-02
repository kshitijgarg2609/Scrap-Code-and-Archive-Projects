#include <DigiCDC.h>
void setup()
{
  SerialUSB.begin();
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Check !!!");
  delay(2000);
  serial();
}

void serial()
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
  Serial.println(m);
}

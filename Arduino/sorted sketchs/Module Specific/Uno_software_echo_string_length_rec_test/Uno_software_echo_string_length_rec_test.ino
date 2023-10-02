#include <SoftwareSerial.h>

SoftwareSerial sp(10, 11);

void setup()
{
  sp.begin(9600);
}

void loop()
{
  if(sp.available())
  {
    sp.println(rec());
  }
}

String rec()
{
  String m="";
  int n=0;
  while(sp.available())
  {
    char c=(char)(sp.read());
    if(c=='\r'||c=='\n')
    {
      continue;
    }
    n++;
    m+=c;
    delay(2);
  }
  return String(n)+":"+m;
}

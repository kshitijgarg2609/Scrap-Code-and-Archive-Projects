#include <SoftSerial_INT0.h>
#include <DigiKeyboard.h>

SoftSerial sp(2,1);           // Software serial port for control the Bluetooth module

String m="";

void setup()
{
    sp.begin(9600); // Initialize the serial port
}

void loop()
{
  //echo();
  rx();
  tx("");
}

void echo()
{
  if(sp.available())
  {
    //String m=rx();
    //tx(m);
  }
}

void rx()
{
  uint8_t n=0;
  while(sp.available())
  {
    //char c=(char)(sp.read());
    //if(c=='\r'||c=='\n')
    //{
      //continue;
    //}
    //n++;
    //m+=c;
    delay(2);
  }
  //sp.flush();
  //m=String(n)+":"+m;
}

void tx(String a)
{
  uint8_t l=a.length();
  for(uint8_t i=0;i<l;i++)
  {
    sp.write(a.charAt(i));
  }
  sp.write('\r');
  sp.write('\n');
  //sp.flush();
}

#include <ESP8266WiFi.h>

int i;

WiFiServer serv(4210);
WiFiClient cli;
boolean tcp_con=false;

void setup()
{
  Serial.begin(115200);
  WiFi.begin("sabka baap","sabkabaap2609");
  serv.begin();
}

void loop()
{
  if(serv.hasClient())
  {
    cli=serv.available();
    tcp_con=true;
  }
  if(tcp_con&&cli.connected())
  {
    if(i=cli.available())
    {
      Serial.println("check available() :- "+String(i));
      uint8_t dta[i];
      cli.read(dta,i);
      cli.flush();
      cli.write(dta,i);
      cli.stop();
      //cli.close();
      tcp_con=false;
    }
    
  }
  else
  {
    tcp_con=false;
  }
}

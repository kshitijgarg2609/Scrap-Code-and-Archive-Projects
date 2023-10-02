#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int i;

IPAddress arr(192,168,2,1);
IPAddress subnet(255,255,255,0);
//IPAddress mul(230,0,0,1);

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //WiFi.softAPConfig(arr,arr,subnet);
  //i=WiFi.softAP("K","123456789");
  WiFi.begin("sabka baap","sabkabaap2609");
  Udp.begin(4210);
}

void loop()
{
  rmsg();
}

void rmsg()
{
  i=Udp.parsePacket();
  if(i>0)
  {
    char rdata[i+1];
    Udp.read(rdata,i);
    rdata[i]='\0';
    Serial.println(String(rdata));
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    while(!Serial.available());
    String r=Rec();
    int l=r.length();
    char arr[l+1];
    for(int j=0;j<l;j++)
    {
      arr[j]=r.charAt(j);
    }
    arr[l]='\0';
    //Udp.write(Rec().c_str());
    Udp.write(arr);
    Udp.endPacket();
  }
}

String Rec()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(2);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  return m;
}

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int i;
String m="";

IPAddress arr(192,168,2,1);
IPAddress subnet(255,255,255,0);

IPAddress broadcast(192,168,2,255);
int dport=4999;

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(arr,arr,subnet);
  i=WiFi.softAP("K","123456789");
  Udp.begin(4210);
}

void loop()
{
  m=readSerial();
  if(m!=""&&m.length()>=7&&m.indexOf("port=")!=-1)
  {
    dport=(m.substring(5)).toInt();
    if(dport>=0)
    {
      Serial.println("PORT SET SUCCESSFULLY !!!");
    }
    else
    {
      Serial.println("PORT SET TO 4999 !!!");
      dport=4999;
    }
  }
  else if(m!=""&&m.length()>=11&&m.indexOf("ip=")!=-1)
  {
    uint8_t i1,i2,i3,i4;
    sscanf(m.c_str(),"ip=%u.%u.%u.%u",&i1,&i2,&i3,&i4);
    if(range(i1)&&range(i2)&&range(i3)&&range(i4))
    {
      broadcast=IPAddress(i1,i2,i3,i4);
      Serial.println("IP SET !!!");
    }
    else
    {
      broadcast=IPAddress(192,168,2,255);
      Serial.println("IP SET TO DEFAULT !!!");
    }
  }
  else if(m!="")
  {
    Serial.println("sending ...   "+m);
    sendMsg(m);
    Serial.println("SENT !!!");
  }
}

boolean range(uint8_t a)
{
  return a>=0&&a<256;
}

void sendMsg(String a)
{
  int l=a.length();
  char arr[l+1];
  Udp.beginPacket(broadcast,dport);
  for(i=0;i<l;i++)
  {
    arr[i]=a.charAt(i);
  }
  arr[l]='\0';
  Udp.write(arr);
  Udp.endPacket();
}

String readSerial()
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
  return m;
}

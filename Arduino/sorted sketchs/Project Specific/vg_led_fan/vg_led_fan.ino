#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int i;

int l1=D2;
int l2=D5;
int l3=D6;
int f1=D8;

IPAddress arr(192,168,2,1);
IPAddress subnet(255,255,255,0);
//IPAddress mul(230,0,0,1);

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(arr,arr,subnet);
  i=WiFi.softAP("K","123456789");
  Udp.begin(4210);
  pinConfig();
}

void pinConfig()
{
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);
  pinMode(f1,OUTPUT);
  analogWrite(l1,0);
  analogWrite(l2,0);
  analogWrite(l3,0);
  analogWrite(f1,0);
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
    //Serial.println(String(rdata));
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //while(!Serial.available());
    String r=cmd(String(rdata));
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

String cmd(String a)
{
  int v1,v2,v3,v4;
  String m="0";
  if(a.length()==12)
  {
    v1=(100*(a.charAt(0)-'0'))+(10*(a.charAt(1)-'0'))+(a.charAt(2)-'0');
    v2=(100*(a.charAt(3)-'0'))+(10*(a.charAt(4)-'0'))+(a.charAt(5)-'0');
    v3=(100*(a.charAt(6)-'0'))+(10*(a.charAt(7)-'0'))+(a.charAt(8)-'0');
    v4=(100*(a.charAt(9)-'0'))+(10*(a.charAt(10)-'0'))+(a.charAt(11)-'0');
    if(range(v1)&&range(v2)&&range(v3)&&range(v4))
    {
      analogWrite(l1,v1);
      analogWrite(l2,v2);
      analogWrite(l3,v3);
      analogWrite(f1,v4);
      return "1";
    }
  }
  return m;
}

boolean range(int a)
{
  return (a>=0&&a<=255);
}

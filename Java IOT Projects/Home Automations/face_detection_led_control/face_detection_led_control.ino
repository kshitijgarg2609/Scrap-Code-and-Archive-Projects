#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;
int port=4210;

int l1=D1;
int l2=D2;
int l3=D5;
int l4=D6;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  udp.begin(port);
  pinSet();
  cmd("0");
  //Serial.begin(115200);
}

void pinSet()
{
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);
  pinMode(l4,OUTPUT);
}

void loop()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    char rdata[i+1];
    udp.read(rdata,i);
    rdata[i]='\0';
    cmd(String(rdata));
    //Serial.println(String(rdata));
  }
}

void cmd(String a)
{
  int L=a.toInt();
  if(L==0)
  {
    zeroLight();
  }
  else if(L==1)
  {
    oneLight();
  }
  else if(L==2)
  {
    twoLight();
  }
  else if(L==3)
  {
    threeLight();
  }
  else if(L>=4)
  {
    fourLight();
  }
}

void zeroLight()
{
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  digitalWrite(l3,LOW);
  digitalWrite(l4,LOW);
}

void oneLight()
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(l3,LOW);
  digitalWrite(l4,LOW);
}

void twoLight()
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,LOW);
  digitalWrite(l4,LOW);
}

void threeLight()
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,LOW);
}

void fourLight()
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
}

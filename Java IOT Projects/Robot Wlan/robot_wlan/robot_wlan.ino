#include <ESP8266WiFi.h>
#include <Servo.h>
#include <WiFiUdp.h>

IPAddress ip(192,168,2,1);
IPAddress subnet(255,255,255,0);

int base=10;

Servo sci,lr,ud,sng;
WiFiUDP Udp;

boolean cnfg=false;
boolean wf=false;

boolean statsci=false;

char arr[5];

void setup()
{
  pin();
  Serial.begin(115200);
  ON();
  arr[0]='@';
  arr[1]='#';
  arr[2]='$';
  arr[3]='%';
  arr[5]='^';
}

void pin()
{
  sci.attach(D2);
  lr.attach(D5);
  ud.attach(D6);
  sng.attach(D8);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
}

void loop()
{
  rmsg();
  delay(1);
  //serialEvent();
}

void rmsg()
{
  int i=Udp.parsePacket();
  if(i>0)
  {
    char rdata[i+1];
    Udp.read(rdata,i);
    rdata[i]='\0';
    Serial.println(String(rdata));
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //while(!Serial.available());
    //String r=Rec();
    /*
    int l=r.length();
    char arr[l+1];
    for(int j=0;j<l;j++)
    {
      arr[j]=r.charAt(j);
    }
    arr[l]='\0';
    */
    control(String(rdata));
    //Udp.write(Rec().c_str());
    //Udp.write(arr);
    //Udp.endPacket();
  }
}


void control(String a)
{
  int ind[5];
  ind[0]=a.indexOf(arr[0]);
  ind[1]=a.indexOf(arr[1]);
  ind[2]=a.indexOf(arr[2]);
  ind[3]=a.indexOf(arr[3]);
  ind[4]=a.indexOf(arr[4]);
  //Serial.println(String(ind[4]));
  String str[6];
  str[0]=a.substring(0,ind[0]);
  str[1]=a.substring(ind[0]+1,ind[1]);
  str[2]=a.substring(ind[1]+1,ind[2]);
  str[3]=a.substring(ind[2]+1,ind[3]);
  str[4]=a.substring(ind[3]+1,ind[4]);
  //str[5]=a.substring(ind[4]+1);
  /*
  Serial.println(str[0]);
  Serial.println(str[1]);
  Serial.println(str[2]);
  Serial.println(str[3]);
  Serial.println(str[4]);
  */
  //sci.write(str[0].toInt());
  sng.write(str[1].toInt());
  controlSpreader(str[0].toInt());
  controlHarvester((a.charAt(a.length()-1))-'0');
  lr.write(str[2].toInt());
  ud.write(str[3].toInt());
  controlRobo(str[4].toInt());
}

void controlHarvester(int a)
{
  //Serial.println(String(a));
  if(a==1)
  {
    //for(int i=1;i<10;i++)
      delay(125);
      sci.write(0);
      delay(125);
      sci.write(96);    
  }
  else
  {
    sng.write(90);
  }
}

void controlSpreader(int a)
{
  if(a==1)
  {
    //for(int i=1;i<10;i++)
    
      delay(75);
      sng.write(30);
      delay(75);
      sng.write(150);    
  }
  else
  {
    sng.write(90);
  }
}

void controlRobo(int a)
{
  if(a==2)
  {
    digitalWrite(D0,HIGH);
    digitalWrite(D1,HIGH);
    delay(50);
  }
  else if(a==1)
  {
    digitalWrite(D0,LOW);
    digitalWrite(D1,HIGH);
    delay(50);
  }
  else if(a==3)
  {
    digitalWrite(D0,HIGH);
    digitalWrite(D1,LOW);
    delay(50);
  }
  else
  {
    digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);
  }
}

void ON()
{
  WiFi.mode(WIFI_AP);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,ip,subnet);
  WiFi.softAP("K","123456789");
  Udp.begin(4210);
}

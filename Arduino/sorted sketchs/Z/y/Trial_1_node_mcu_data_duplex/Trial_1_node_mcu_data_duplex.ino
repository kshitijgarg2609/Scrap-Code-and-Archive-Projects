#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int dvc=0;

String id="";

String m; //Command reciever
String msg;
int i;

boolean con=false; //WiFi connection flag
boolean act=false; 
boolean ht=false; //Hotspot ON Flag
boolean flg=true;

// user-password
String user="echomation";
String pass="echomation";

//IP Configurations
IPAddress arr[3];
IPAddress subnet(255,255,255,0);

String tmp;
// UDP
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
//char
String replyPacket;  // a reply string to send back

//Appliances
int led1=D0;

void setup()
{
  //Pin configuration
  pinMode(led1,OUTPUT);
  digitalWrite(led1,LOW);
  //ID initializations
  arr[0]=IPAddress(192,168,7,1);
  arr[1]=IPAddress(192,168,8,1);
  arr[2]=IPAddress(192,168,9,1);
  if(dvc==0)
  {
    id="A";
  }
  else if(dvc==1)
  {
    id="B";
  }
  else if(dvc==2)
  {
    id="C";
  }
  replyPacket="Router : "+id;
  //WiFi configuration now
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(arr[dvc],arr[dvc],subnet);
  ht=WiFi.softAP(user.c_str(),pass.c_str(),6,false,5);
  WiFi.begin(user.c_str(),pass.c_str());
  //WiFi.softAPdisconnect(false);
  delay(2000);
  if(ht)
  {
    Serial.println("HOTSPOT STARTED SUCCESSFULLY !!!");
  }
  else
  {
    Serial.println("COULDN'T START HOSTSPOT !!!");
  }
  Udp.begin(localUdpPort);
  act=true;
}

void loop()
{
  m="";
  delay(150);
  m=rpack();
  if(m!="")
  {
    flg=false;
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    if(m.equals("$"))
    {
      Udp.write(replyPacket.c_str());
    }
    else if(m.equals((id+":LIGHT ON")))
    {
      digitalWrite(led1,HIGH);
      Udp.write(m.c_str());
    }
    else if(m.equals((id+":LIGHT OFF")))
    {
      digitalWrite(led1,LOW);
      Udp.write(m.c_str());
    }
    Udp.endPacket();
    flg=true;
  }
}

String rpack()
{
  m="";
  char c='\0';
    while(Udp.available()>0)
    {
      c=Udp.read();
      if(c=='\n')
      {
        break;
      }
      delay(1);
      m+=c;
    }
    Udp.flush();
   return m;
}

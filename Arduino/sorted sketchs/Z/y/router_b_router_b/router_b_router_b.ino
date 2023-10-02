#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int dvc=1;

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
int fan=D1;
int door=D2;

void setup()
{
  //Pin configuration
  pinMode(led1,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(door,OUTPUT);
  digitalWrite(led1,LOW);
  digitalWrite(fan,LOW);
  digitalWrite(door,LOW);
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
  ht=WiFi.softAP(user.c_str(),pass.c_str());//,6,false,8);
  WiFi.begin(user.c_str(),pass.c_str());
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
  Serial.begin(115200);
}

void loop()
{
  delay(250);
  m=rmsg();
  if(m!="")
  {
    cmd(m);
  }
  //
  if(flg)
  {
    int packetSize = Udp.parsePacket();
    if (packetSize!=0)
    {
      flg=false;
    // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      //Udp.flush();
      if(len>0)
      {
        incomingPacket[len] = 0;
      }
      delay(20);
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      m=convert(incomingPacket);
      Serial.println(m);
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      if(m.equals("$"))
      {
        msg=replyPacket;
        Udp.write(msg.c_str());
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
      else if(m.equals("FAN ON"))
      {
        digitalWrite(fan,HIGH);
        Udp.write(m.c_str());
      }
      else if(m.equals("FAN OFF"))
      {
        digitalWrite(fan,LOW);
        Udp.write(m.c_str());
      }
      else if(m.equals("DOOR OPEN"))
      {
        digitalWrite(door,HIGH);
        Udp.write(m.c_str());
      }
      else if(m.equals("DOOR CLOSE"))
      {
        digitalWrite(door,LOW);
        Udp.write(m.c_str());
      }
      Udp.endPacket();
      flg=true;
    }
  }
}

void cmd(String a)
{
  if(a.equals("id"))
  {
    Serial.println("ID : "+id);
  }
  else if(a.equals("status"))
  {
    if(con)
    {
      Serial.println("WiFi status : connected");
    }
    else
    {
      Serial.println("WiFi status : not connected");  
    }
  }
  else if(con&&a.equals("info"))
  {
    Serial.println("WiFi Local IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("Subnet Mask : ");
    Serial.println(WiFi.subnetMask());
    Serial.println("Gateway : ");
    Serial.println(WiFi.gatewayIP());
  }
}



String rmsg()
{
  m="";
  char c='\0';
    while(Serial.available()>0)
    {
      c=Serial.read();
      if(c=='\n')
      {
        break;
      }
      delay(1);
      m+=c;
    }
    Serial.flush();
   return m;
}

String convert(char *str)
{
  String a="";
  for(i=0;i<strlen(str);i++)
  {
    a+=str[i];
  }
  return a;
}

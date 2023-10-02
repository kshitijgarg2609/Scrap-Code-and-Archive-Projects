#include<ESP8266WiFi.h>
#include<WiFiUdp.h>

int i;
int port=4210;

WiFiUDP udp;

IPAddress ip(192,168,1,1);
IPAddress sub(255,255,255,0);
char incomingPacket[255];
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,ip,sub);
  WiFi.softAP("K","123456789");
  udp.begin(port);
  //pinMode(D5,OUTPUT);
}

void loop()
{
//  if(i=udp.parsePacket())
//  {
//    char rdta[i+1];
//    udp.read(rdta,i);
//    rdta[i]='\0';
//    Serial.println(String(rdta));
//  }
  int packetSize = udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
  int len = udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = '\0';
    }
   Serial.printf("UDP packet contents: %s\n", incomingPacket);
    /*
    if(String(incomingPacket).equalsIgnoreCase("on")){
      digitalWrite(D5, HIGH);
    }
    else if(String(incomingPacket).equalsIgnoreCase("off")){
      digitalWrite(D5,LOW);
    }*/
}
}

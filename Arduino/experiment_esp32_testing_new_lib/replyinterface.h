static WiFiUDP udp;
static boolean udp_flg=false;
static String udp_data="";

static IPAddress rem_ip(192,168,4,255);
static int rem_port=4210;

void initUdp()
{
  udp.begin(4210);
}

boolean udpPacket()
{
  int i=udp.parsePacket();
  if(i>0)
  {
    uint8_t dta[i];
    udp.read(dta,i);
    udp_data="";
    rem_ip=udp.remoteIP();
    rem_port=udp.remotePort();
    for(int j=0;j<i;j++)
    {
      udp_data+=(char)(dta[j]);
    }
    return true;
  }
  return false;
}

void replyToSerial(String a)
{
  Serial.println(a);
}

void replyToUdp(String a)
{
  int l=a.length();
  uint8_t dta[l];
  for(int i=0;i<l;i++)
  {
    dta[i]=(uint8_t)(a.charAt(i));
  }
  udp.beginPacket(rem_ip,rem_port);
  udp.write(dta,l);
  udp.endPacket();
}

void replyBack(String a)
{
  if(udp_flg)
  {
    replyToUdp(a);
  }
  else
  {
    replyToSerial(a);
  }
}

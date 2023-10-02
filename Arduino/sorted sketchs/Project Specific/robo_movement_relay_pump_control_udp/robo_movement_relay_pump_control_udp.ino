#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int i;

IPAddress arr(192,168,2,1);
IPAddress subnet(255,255,255,0);
//IPAddress mul(230,0,0,1);

WiFiUDP Udp;

int IN=D0; //Pump
int IN1=D1; // Left Forward
int IN2=D2; // Left Backward

//serial 
int lm;
char c;
//timing
boolean tflg=false;
long etime=0;
long timeout=500;

void setup()
{
  pinsetup();
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(arr,arr,subnet);
  i=WiFi.softAP("K","123456789");
  Udp.begin(4210);
}

void pinsetup()
{
  pinMode(IN,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  initState();
}

void initState()
{
  operation(0);
  wPump(false);
}

void loop()
{
  if(tflg&&((millis()-etime)>=timeout))
  {
    //Serial.println("flag off");
    tflg=false;
    initState();
  }
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
    //Serial.println(r);
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
  lm=a.length();
  if(lm==5&&(a.indexOf("op:")!=-1))
  {
    c=a.charAt(3);
    if(c>='0'&&c<='5')
    {
      tflg=true;
      //Serial.println("PREVIOUS ETIME : "+String(etime));
      //Serial.println("ELAPSING : "+String(millis()-etime));
      etime=millis();
      //Serial.println("NEXT ETIME : "+String(etime));
      operation(c-'0');
      wPump(a.charAt(4)=='1');
      return "1";
    }
    else
    {
      tflg=false;
      Serial.println("0");
    }
  }
  else if(lm>=4&&(a.indexOf("t=")!=-1))
  {
    int tnum=(a.substring(2)).toInt();
    if(tnum>=10)
    {
      timeout=tnum;
      return "Timeout set !!!";
    }
    else
    {
      return "Timeout couldn't be set !!!";
    }
  }
  else
  {
    return "Invalid Command !!!";
  }
}

//movement functions
void operation(int a)
{
  if(a==0)
  {
    stopMoving();
  }
  else if(a==1)
  {
    MoveLeft();
  }
  else if(a==2)
  {
    MoveRight();
  }
  else if(a==3)
  {
    MoveForward();
  }
}

void stopMoving()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
}

void MoveLeft()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void MoveRight()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void MoveForward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

//pump function
void wPump(boolean a)
{
  if(a)
  {
    digitalWrite(IN,LOW);
  }
  else
  {
    digitalWrite(IN,HIGH);
  }
}

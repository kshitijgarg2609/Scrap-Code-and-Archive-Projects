#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

#define FIREBASE_HOST "demonstration-49368-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "bzo9ZWF22xbjGUyPKkZ9p6HS6LKJLj5owsR4hydX"
#define WIFI_SSID "xyz"
#define WIFI_PASSWORD "123456789"

String m;             //String input

Servo sv_1;
int start;
boolean a1;
int x1;          //position of servo arm

int motor,angle;

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);

//int x;

void setup()
{
  a1=false;
  start=0;
  pinMode(D2,OUTPUT);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  //Firebase.setInt(firebaseData,"/led",0);
}

void loop()
{
  Firebase.getString(firebaseData,"/");
  if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
    cmd(firebaseData.stringData());
    Firebase.setString(firebaseData,"/","");
  }
  firebaseData.clear();
  delay(2);
}

void activate(int m,int pos,int pin)
{
  if(m==1)
  {
    sv_1.attach(D2);
    sv_1.write(pos);
    a1=true;
  }
}

void moveArm(int m,int pos)
{
  if(m==1&&a1)
  {
    sv_1.write(pos);
  }

  else
  {
    Serial.println("UNCONFIGURED PIN !!!");
  }
}

boolean separate(String a)
{
  if(a.length()>=3&&toNumber(a)!=-1&&a.indexOf('0')==1)
  {
    motor=toNumber(a.substring(0,1));
    angle=toNumber(a.substring(2));
    return ((motor==1)&&(angle>=0&&angle<=180));
  }
  else
  {
    return false;
  }
}

void invalid()
{
  Serial.println("INVALID COMMAND !!!");
}

void cmd(String a)
{
  int seg1,seg2,pinN;
  if(separate(a))
  {
    moveArm(motor,angle);
  }
  else if(a.length()>4&&a.indexOf("set")==0)
  {
    seg1=a.indexOf(' ');
    seg2=a.lastIndexOf('#');
    if(seg1!=-1&&seg2!=-1&&seg2<(a.length()-1)&&(seg2-seg1)>1)
    {
      pinN=toNumber(a.substring(seg2+1));
       if(pinN!=-1&&separate(a.substring(seg1+1,seg2)))
       {
         Serial.println("ACTIVATED !!!");
         activate(motor,angle,pinN);
       }
      else
      {
        invalid();
      }
    }
    else
    {
      invalid();
    }
  }
  else
  {
    invalid();
  }
}

int toNumber(String a)
{
  int x=1,i;
  char c;
  for(i=0;i<a.length();i++)
  {
    c=a.charAt(i);
    if(c<48||c>57)
    {
      return -1;
    }
  }
  return a.toInt();
}

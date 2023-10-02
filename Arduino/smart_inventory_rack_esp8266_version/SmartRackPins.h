#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <DHT.h>
#include "pins.h"

void initSystem();
void initAddress();
void scheduler();
void unscheduler();
String pushState();
void loadAll();
void writeAll();
void setDefault();
void loadStructure(int);
void writeStructure(int);
void regulatePropeller();
String dht();

boolean dur=false;
DateTime p;

DS3231 rtc;
DateTime dt;
TimeDelta td;


DHT dht11(sensor_ht_pin,DHT11);

int cutoff=50;
int analog=100;

int fan=0;

typedef struct dataset
{
  char fil,sch,wst;
  DateTime dt;
}dataset;

dataset arr[6];

int addr[6];

void initSystem()
{
  Wire.begin(clock_sck,clock_scl);
  rtc.begin();
  EEPROM.begin(100);
  dht11.begin();
  initAddress();
  initPin();
  loadAll();
  for(int i=0;i<6;i++)
  {
    if((arr[i].fil!='1'&&arr[i].fil!='0')||(arr[i].sch!='1'&&arr[i].sch!='0')||(arr[i].wst!='1'&&arr[i].wst!='0'))
    {
      setDefault();
      break;
    }
  }
}

void process()
{
  scheduler();
  unscheduler();
  regulatePropeller();
}

void initAddress()
{
  addr[0]=10;
  addr[1]=20;
  addr[2]=30;
  addr[3]=40;
  addr[4]=50;
  addr[5]=60;
}

void scheduler()
{
  boolean oc=false;
  char fil,sch,wst;
  String str=pushState();
  for(int i=0;i<6;i++)
  {
    if(str.charAt(i)=='1'&&arr[i].fil=='0')
    {
      arr[i].fil='1';
      if(dur==true)
      {
        oc=true;
        arr[i].sch='1';
        arr[i].dt=p;
      }
      writeStructure(i);
    }
  }
  if(oc)
  {
    dur=false;
  }
}

void unscheduler()
{
  char fil,sch,wst;
  String str=pushState();
  DateTime ftch;
  for(int i=0;i<6;i++)
  {
    if(str.charAt(i)=='0'&&arr[i].fil=='1')
    {
      arr[i].fil='0';
      arr[i].sch='0';
      arr[i].wst='0';
      writeStructure(i);
    }
    else if(str.charAt(i)=='1'&&arr[i].fil=='1')
    {
      if(arr[i].sch=='1')
      {
        if(arr[i].dt<=rtc.now())
        {
          arr[i].sch='0';
          arr[i].wst='1';
          writeStructure(i);
        }
      }
    }
  }
}

String pushState()
{
  String tmp="";
  for(int i=0;i<6;i++)
  {
    char c;
    if(digitalRead(pb_pin[i])==LOW)
    {
      c='1';
    }
    else
    {
      c='0';
    }
    tmp+=c;
  }
  return tmp;
}

void loadAll()
{
  for(int i=0;i<6;i++)
  {
    loadStructure(i);
  }
}

void writeAll()
{
  for(int i=0;i<6;i++)
  {
    writeStructure(i);
  }
}

void setDefault()
{
  for(int i=0;i<6;i++)
  {
    arr[i].fil='0';
    arr[i].sch='0';
    arr[i].wst='0';
    arr[i].dt=DateTime();
  }
  writeAll();
}

void loadStructure(int i)
{
  EEPROM.get(addr[i],arr[i]);
}

void writeStructure(int i)
{
  EEPROM.put(addr[i],arr[i]);
  EEPROM.commit();
}

void regulatePropeller()
{
  String a=dht();
  float humid;
  a=a.substring(a.lastIndexOf(":")+1);
  humid=a.toFloat();
  fan=analog+((humid-cutoff)*4);
  if(fan>=255)
  {
    fan=255;
  }
  analogWrite(fpin,fan);
}

String dht()
{
  String dhtt="dht:";
  float temp,humid;
  temp = dht11.readTemperature();
  humid = dht11.readHumidity();
  return dhtt+String(temp)+":"+String(humid);
}

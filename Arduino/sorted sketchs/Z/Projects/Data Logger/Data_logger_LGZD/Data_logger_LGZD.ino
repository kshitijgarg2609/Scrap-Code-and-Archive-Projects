#include <ArduinoLowPower.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <SD.h>
//----------------------------------------------------------------------
//Pin Configuration
int clk=7;
int dat=6;
int rst=5;

int ss=9;

int turbidity=A0;
//----------------------------------------------------------------------
//Device Object
LiquidCrystal_I2C lcd(0x27,16,2);
virtuabotixRTC ds(clk,dat,rst);
File ff;
//----------------------------------------------------------------------
//Working Variables
String tmp;
String tuple;
int i,j;
int snap;
boolean slp;
//----------------------------------------------------------------------
//DataSets
String fname="LGZD.txt";
boolean stat[2];
char timest[8];
char datest[10];
String sdstat;
String lgzd;
//----------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  SD.begin(ss);
  snap=millis();
  slp=false;
}

void loop()
{
  tuple=getTuple();
  writeLog(tuple);
  Serial.println(tuple);
  delay(1000);
}

//----------------------------------------------------------------------
//Data Assembly
String getTuple()
{
  tuple="";
  tuple+=stampDateTime()+","+getNTU();
  //LCD
  lcd.setCursor(4,0);
  lcd.print(com(lgzd,10));
  delay(5);
  lcd.setCursor(4,1);
  lcd.print(sdstat);
  return tuple;
}

String com(String str,int tspace)
{
  i=tspace-str.length();
  for(j=1;j<=i;j++)
  {
    str+=" ";
  }
  return str;
}

//----------------------------------------------------------------------
//DS1302

String fetchTime()
{
  int tmptime;
  tmptime=ds.hours;
  timest[0]=(tmptime/10)+48;
  timest[1]=(tmptime%10)+48;
  timest[2]=':';
  tmptime=ds.minutes;
  timest[3]=(tmptime/10)+48;
  timest[4]=(tmptime%10)+48;
  timest[5]=':';
  tmptime=ds.seconds;
  timest[6]=(tmptime/10)+48;
  timest[7]=(tmptime%10)+48;
  tmp="";
  for(i=0;i<8;i++)
  {
    tmp+=timest[i];
  }
  return tmp;
}

String fetchDate()
{
  int tmpdate;
  tmpdate=ds.dayofmonth;
  datest[0]=(tmpdate/10)+48;
  datest[1]=(tmpdate%10)+48;
  datest[2]='-';
  tmpdate=ds.month;
  datest[3]=(tmpdate/10)+48;
  datest[4]=(tmpdate%10)+48;
  datest[5]='-';
  tmpdate=ds.year;
  datest[6]=(tmpdate/1000)+48;
  datest[7]=((tmpdate/100)%10)+48;
  datest[8]=((tmpdate/10)%10)+48;
  datest[9]=(tmpdate%10)+48;
  tmp="";
  for(i=0;i<10;i++)
  {
    tmp+=datest[i];
  }
  return tmp;
}

String stampDateTime()
{
  ds.updateTime();
  return fetchDate()+","+fetchTime();
}

//----------------------------------------------------------------------
//SD Card Adapter


void writeLog(String lg)
{
  ff=SD.open(fname,FILE_WRITE);
  if(ff)
  {
    sdstat="SD: OK";
    Serial.println("LOGGING !!!");
    ff.println(lg);
  }
  else
  {
    sdstat="SD:ERR";
    Serial.println("NOT LOGGING !!!");
    SD.begin(ss);
  }
  ff.close();
}

//----------------------------------------------------------------------
//LGZD
String getNTU()
{
  float vol=((float)analogRead(turbidity)/1024.0)*5.0;
  float fntu=-1120.4*square(vol)+5742.3*vol-4353.8;
  fntu+=180;
  if(fntu>0&&fntu<=3000)
  {
    lgzd=String(fntu)+" ntu";
    return lgzd;
  }
  else
  {
    lgzd="err";
    return "err";
  }
}

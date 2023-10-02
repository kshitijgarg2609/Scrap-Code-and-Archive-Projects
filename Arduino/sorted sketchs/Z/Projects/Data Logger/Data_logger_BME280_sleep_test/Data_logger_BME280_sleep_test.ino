#include <Sleep_n0m1.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//----------------------------------------------------------------------
//Pin Configuration
int clk=7;
int dat=6;
int rst=5;

int ss=10;
//----------------------------------------------------------------------
//Device Object
LiquidCrystal_I2C lcd(0x27,16,2);
virtuabotixRTC ds(clk,dat,rst);
File ff;
Adafruit_BME280 bme;
Sleep slp;
//----------------------------------------------------------------------
//Working Variables
String tmp;
String tuple;
int i,j;
int del=20000;
//----------------------------------------------------------------------
//DataSets
String fname="BME280.txt";
boolean stat[2];
char timest[8];
char datest[10];
String sdstat;
String h,t,p;
//----------------------------------------------------------------------

void setup()
{
  initializ();
  delay(5000);
  //testing
  slp.idleMode(); //set sleep mode
  slp.sleepDelay(5000);
  initializ();
}

void initializ()
{
  Serial.begin(9600);
  lcd.begin();
  SD.begin(ss);
  bme.begin();
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
  tuple+=stampDateTime()+","+readBME();
  //LCD
  lcd.setCursor(1,0);
  delay(10);
  lcd.print(com(h,6));
  delay(10);
  lcd.setCursor(9,0);
  delay(10);
  lcd.print(com(t,6));
  delay(10);
  lcd.setCursor(0,1);
  delay(10);
  lcd.print(com(p,9));
  delay(10);
  lcd.setCursor(14,1);
  delay(10);
  lcd.print(sdstat);
  return tuple;
}

String com(String str,int tspace)
{
  i=tspace-str.length()+1;
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
    sdstat="SD";
    Serial.println("LOGGING !!!");
    ff.println(lg);
  }
  else
  {
    sdstat="ER";
    Serial.println("NOT LOGGING !!!");
    SD.begin(ss);
  }
  ff.close();
}

//----------------------------------------------------------------------
//BME 280
String readBME()
{
  float hum,tem,pres;
  hum=bme.readHumidity();
  tem=bme.readTemperature();
  pres=(bme.readPressure()/100.0F);
  if(isnan(hum)||isnan(tem)||isnan(pres))
  {
    bme.begin();
    h="err";
    t="err";
    p="err";
    return "err,err,err";
  }
  else if((hum>=0 && hum<=100)&&(tem>=(-40)&&tem<=85)&&(pres>=300&&pres<=1100))
  {
    h=String(hum)+"%";
    t=String(tem)+"C";
    p=String(pres)+"nPa";
    return (String(hum)+" %,"+String(tem)+" C,"+String(pres)+" nPa");
  }
  else
  {
    h="err";
    t="err";
    p="err";
    return "err,err,err";
  }
}

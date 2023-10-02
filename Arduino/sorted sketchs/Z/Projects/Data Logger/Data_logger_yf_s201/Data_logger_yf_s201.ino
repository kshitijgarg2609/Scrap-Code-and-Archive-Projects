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

int wpin=3;
float f,r=0;
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
//----------------------------------------------------------------------
//DataSets
String fname="yf_s201.txt";
boolean stat[2];
char timest[8];
char datest[10];
String sdstat;
String wtrf;
//----------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  SD.begin(ss);
  pinMode(wpin,INPUT);
  //attachInterrupt(digitalPinToInterrupt(2),measure,LOW);
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
  tuple+=stampDateTime()+","+getLM();
  //LCD
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
//YF-S102
String getLM()
{
  float val=r;
  if(val<=30)
  {
    return String(r)+" L/m"; 
  }
  else
  {
    return "err";
  }
}

String getLMDisplay()
{
  return String(r)+" L/m";
}
void measure()
{
  f=pulseIn(wpin,HIGH)+pulseIn(wpin,LOW);
  if(f!=0)
  {
    f=1000000.0/f;
  }
  r=f/7.5;
  if(r<=30)
  {
    delay(4);
    lcd.setCursor(4,0);
    delay(4);
    lcd.print(com(getLMDisplay(),10));
  }
  else
  {
    delay(4);
    lcd.setCursor(4,0);
    delay(4);
    lcd.print(com("err",10));
  }
}

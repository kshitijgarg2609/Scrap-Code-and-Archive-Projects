#include <SPI.h>
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <SD.h>
//----------------------------------------------------------------------
//Pin Configuration
int clk=7;
int dat=6;
int rst=5;

int ss=10;

int turbidity=A0;
//----------------------------------------------------------------------
//Device Object
//LiquidCrystal_I2C lcd(0x27,16,2);
virtuabotixRTC ds(clk,dat,rst);
File ff;
//----------------------------------------------------------------------
//Working Variables
String tmp;
String tuple;
int i,j;
String m;
boolean rgps=false;
String ser;
//----------------------------------------------------------------------
//DataSets
String fname="GPS.txt";
boolean stat[2];
char timest[8];
char datest[10];
String sdstat;
String caploc="err";
String gps1="err";
String gps2="err";
//----------------------------------------------------------------------

void setup()
{
  ds.setDS1302Time(00, 1, 1, 6, 7, 7, 2019);
  Serial.begin(9600);
  Serial1.begin(9600);
  //lcd.begin();
  //SD.begin(ss);
}

void loop()
{
  //writeLog(getLoc());
  //Serial.println(getLoc());
  tuple=getTuple();
  Serial.println(tuple+"______________________"+ser);
  delay(1000);
}

//----------------------------------------------------------------------
//Data Assembly
String getTuple()
{
  tuple="";
  //tuple+=stampDateTime()+","+getLoc();
  tuple+=getLoc();
  /*
  lcd.setCursor(0,0);
  lcd.print(com(gps1,13));
  lcd.setCursor(0,1);
  lcd.print(com(gps2,13));
  lcd.setCursor(14,0);
  lcd.print(sdstat);*/
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
    sdstat="SD";
    //Serial.println("LOGGING !!!");
    ff.println(lg);
  }
  else
  {
    sdstat="ER";
    //Serial.println("NOT LOGGING !!!");
    SD.begin(ss);
  }
  ff.close();
}

//----------------------------------------------------------------------
//GPS
String getLoc()
{
  int gsn;
  caploc="err";
  gps1="err";
  gps2="err";
  i=millis();
  for(i=1;i<=10&&(millis()-i)<=1500;i++)
  {
    gsn=millis();
    rgps=true;
    while((rgps==true)&&((millis()-gsn)<=1500));
    caploc=gps(ser);
    //Serial.println("current received data : "+ser);
    if(caploc!="err"||!caploc.equals("err"))
    {
      j=caploc.indexOf(' ');
      gps1=caploc.substring(0,j);
      gps2=caploc.substring(j+1);
      break;
    }
    if(rgps==false)
    {
      i--;
    }
  }
  return caploc;
}

void serialEvent1()
{
  
  //rgps=true;
  if(rgps==true)
  {
    Serial.println("test");
    //ser=Serial1.readString();
    ser=rmsg1();
    //Serial.println("current received data : "+ser);
    rgps=false;
  }
  else
  {
    tmp=rmsg1();
  }
}

String gps(String a)
{
  String loc="err";
  float deci;
  int ins,iew;
  String div1,div2;
  if(a.indexOf("GPRMC")!=-1&&a.indexOf("A")==17)
  {
    if((ins=a.indexOf('N'))!=-1)
    {
      div1=a.substring(0,ins-1);
      div1=div1.substring(div1.lastIndexOf(',')+1,ins-1);
    }
    else if((ins=a.indexOf('S'))!=-1)
    {
      div1=a.substring(0,ins-1);
      div1=div1.substring(div1.lastIndexOf(',')+1,ins-1);
    }
    else
    {
      return loc;
    }
    if((iew=a.indexOf('E'))!=-1)
    {
      div2=a.substring(ins+2,iew-1);
    }
    else if((iew=a.indexOf('W'))!=-1)
    {
      div2=a.substring(ins+2,iew-1);
    }
    else
    {
      return loc;
    }
    deci=div1.toFloat();
    deci=60*(deci-((int)deci));
    loc=String(div1.substring(0,2).toInt())+"*"+String(div1.substring(2,4).toInt())+(char)(39);
    loc+=String(deci)+(char)(34)+a.charAt(ins)+" ";
    
    deci=div2.toFloat();
    deci=60*(deci-((int)deci));
    loc+=String(div2.substring(0,3).toInt())+"*"+String(div2.substring(3,5).toInt())+(char)(39);
    loc+=String(deci)+(char)(34)+a.charAt(iew);
    return loc;
  }
  return loc;
}

String rmsg1()
{
  m="";
  char c='\0';
    while(Serial1.available()>0)
    {
      c=Serial1.read();
      /*
      if(c=='\n'||c=='\r')
      {
        if(Serial1.available()>0)
        {
          c=Serial1.read();
        }
        break;
      }*/
      //delay(2);
      m+=c;
    }
    //Serial1.flush();
   return m;
}

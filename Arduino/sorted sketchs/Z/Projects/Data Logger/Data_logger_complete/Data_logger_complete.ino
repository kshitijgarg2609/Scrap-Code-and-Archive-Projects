#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//----------------------------------------------------------------------
//Pin Configuration
int rs=22;
int en=23;
int d4=24;
int d5=25;
int d6=26;
int d7=27;
int cont=2;

int clk=7;
int dat=6;
int rst=5;

int ss=9;

int turbidity=A0;

int wpin=8;
//----------------------------------------------------------------------
//Device Object
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
virtuabotixRTC ds(clk,dat,rst);
File ff;
Adafruit_BME280 bme;
//----------------------------------------------------------------------
//Working Variables
String tmp;
String tuple;
int i,j;
String m;
int gpst=10;
boolean rgps=true;
//----------------------------------------------------------------------
//DataSets
String fname="TEST.txt";
boolean stat[2];
char timest[8];
char datest[10];
String sdstat;
String htp;
String caploc="err";
String gps1="err";
String gps2="err";
String lgzd;
String wtrf;
//----------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(cont,OUTPUT);
  analogWrite(cont,74);
  lcd.begin(20,4);
  SD.begin(ss);
  bme.begin();
  pinMode(wpin,INPUT);
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
  tuple+=stampDateTime()+","+readBME()+","+getLoc()+","+getNTU()+","+getLM();
  //LCD
  lcd.setCursor(0,0);
  lcd.print(com(htp,20));
  delay(20);
  lcd.setCursor(0,1);
  lcd.print(com(gps1,13));
  delay(20);
  lcd.setCursor(0,2);
  lcd.print(com(gps2,13));
  delay(20);
  lcd.setCursor(0,3);
  lcd.print(com(lgzd,7));
  delay(20);
  lcd.setCursor(8,3);
  lcd.print(com(wtrf,5));
  delay(20);
  lcd.setCursor(14,2);
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
    htp="err   err    err";
    return "err,err,err";
  }
  else if((hum>=0 && hum<=100)&&(tem>=(-40)&&tem<=85)&&(pres>=300&&pres<=1100))
  {
    htp=String(hum)+" "+String(tem)+" "+String(pres);
    return (String(hum)+" %,"+String(tem)+" C,"+String(pres)+" nPa");
  }
  else
  {
    htp="err   err    err";
    return "err,err,err";
  }
}
//----------------------------------------------------------------------
//GPS
String getLoc()
{
  int gsnap=millis();
  rgps=true;
  while(rgps==true&&((millis()-gsnap)<=10));
  return caploc;
}

void serialEvent1()
{
  //Serial.println("event called !!!");
  m=rmsg1();
  if(rgps==true)
  {
    //Serial.println("if true !!!");
    m=gps(m);
    //Serial.println(m);
    if(m!="err"||!m.equals("err"))
    {
      caploc=m;
      gpst=caploc.indexOf(' ');
      gps1=caploc.substring(0,gpst);
      gps2=caploc.substring(gpst+1);
      gpst=10;
      rgps=false;
      //Serial.println(m);
    }
    else if(gpst!=1)
    {
      gpst=(gpst>1)?gpst-1:gpst;
    }
    else
    {
      rgps=false;
      caploc="err";
      gps1="err";
      gps2="err";
      //Serial.println("error");
    }
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
      if(c=='\n'||c=='\r')
      {
        if(Serial1.available()>0)
        {
          c=Serial1.read();
        }
        break;
      }
      delay(2);
      m+=c;
    }
    Serial1.flush();
   return m;
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
    lgzd=String(fntu);
    return String(fntu)+" ntu";
  }
  else
  {
    lgzd="err";
    return "err";
  }
}
//----------------------------------------------------------------------
//YF-S102
String getLM()
{
  String wter;
  float wrate;
  int hval,lval,tm;
  while(true)
  {
    tm=millis();
    hval=pulseIn(wpin,HIGH);
    tm=millis()-tm;
    if(tm>=680)
    {
      wrate=0;
      break;
    }
    lval=pulseIn(wpin,LOW);
    wrate=1000000.0/(hval+lval);
    wrate/=7.5;
    if(wrate<0)
    {
      continue;
    }
    else if(wrate>=0&&wrate<=30)
    {
      break;
    }
    else if(wrate>30)
    {
      wter="err";
      wrate=-1;
      break; 
    }
  }
  wtrf=String(wrate);
  wter=String(wrate)+" L/m";
  return wter;
}

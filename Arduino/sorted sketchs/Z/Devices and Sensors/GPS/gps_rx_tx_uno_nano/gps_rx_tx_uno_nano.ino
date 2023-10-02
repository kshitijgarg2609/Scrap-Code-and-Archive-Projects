String m;
int gpst=10;

boolean rgps=true;

String caploc="";

void setup()
{
  Serial.begin(9600);
  //Serial1.begin(9600);
}

void loop()
{
  //Serial.println(caploc);
  //caploc="err";
  Serial.println(getLoc());
  Serial.println("check");
  delay(1000);
}

String getLoc()
{
  int gsnap=millis();
  rgps=true;
  while(rgps==true&&((millis()-gsnap)<=1000));
  return caploc;
}

void serialEvent()
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
      gpst=10;
      caploc=m;
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
    while(Serial.available()>0)
    {
      c=Serial.read();
      if(c=='\n'||c=='\r')
      {
        if(Serial.available()>0)
        {
          c=Serial.read();
        }
        break;
      }
      delay(2);
      m+=c;
    }
    Serial.flush();
   return m;
}

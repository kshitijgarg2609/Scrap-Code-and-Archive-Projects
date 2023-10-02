#include <Servo.h>
#include <EEPROM.h>

Servo sv;

int servo_pin=9;    //sevo pin
int pos=90;          //position of servo arm

int flg=0;          //flag for ping distance
int echo=6;         //echo pin
int trig=7;         //trigger pin
float val;          //current distance value
float ld;

int i;
int j;

char ldd;
char fbit;

int mloc=0;
int active=0;

float park[3][6];
char o[6];

void setup()
{
  EEPROM.get(0,fbit);
  if(!(fbit=='0'||fbit=='1'))
  {
    saveToRom(0);
  }
  loadFromRom();
  Serial.begin(9600);
  sv.attach(servo_pin);
  sv.write(pos);
}

void loop()
{
  String rec;
  rec=rmsg();
  if(rec!="")
  {
    cmd(rec);
  }
  if(flg==1)
  {
    pingdistance();
  }
  if(active==1)
  {
    simulate();
    delay(400);
  }
}

String rmsg()
{
  String rec="";  
  if(Serial.available()>0)
  {
  rec=Serial.readString();
  rec=rec.substring(0,rec.length()-1);
  }
  return rec; 
}


void saveToRom(int x)
{
  fbit=(x==0)?'0':'1';
  EEPROM.put(0,fbit);
  mloc=1;
  for(i=0;i<3;i++)
  {
    for(j=0;j<6;j++)
    {
      ld=(x==0)?(-1):(park[i][j]);
      EEPROM.put(mloc,ld);
      mloc+=sizeof(float);
    }
  }
}

void loadFromRom()
{
  mloc=1;
  for(i=0;i<3;i++)
  {
    for(j=0;j<6;j++)
    {
      EEPROM.get(mloc,ld);
      mloc+=sizeof(float);
      park[i][j]=ld;
    }
  }
}

String UpperCase(String a)
{
  String ustr="";
  int i;
  char c;
  for(i=0;i<a.length();i++)
  {
    c=a.charAt(i);
    ustr+=(c>=97&&c<=122)?(char)(c-32):c;
  }
  return ustr;
}

void cmd(String a)
{
  int x,i,j;
  a=UpperCase(a);
  //MOV
  if(a.length()>4&&a.indexOf("MOV ")==0)
  {
    x=toNumber(a.substring(4));
    if(x>=0&&x<=180)
    {
      pos=x;
      sv.write(x);
      Serial.println("Moved!");
    }
    else
    {
      invalid();
    }
  }
  //PING
  else if(a.indexOf("PING")==0)
  {
    flg=1;
    Serial.println("Starting ping Distance !");
  }
  //STOP
  else if(a.indexOf("STOP")==0)
  {
    flg=0;
    Serial.println("Stopping ping Distance !");
  }
  //SET
  else if(a.length()>4&&a.indexOf("SET ")==0)
  {
    if(flg==1)
    {
      x=toNumber(a.substring(4));
      x=check(x);
      if(x==-1)
      {
        Serial.println("ENTER A VALID SLOT !");
        return;
      }
      i=x/10;   //slot number
      j=x%10;   //bound number
      park[0][i-1]=(float)pos;
      park[j][i-1]=val;
      flg=0;
      Serial.println("VALUE IS SET !");
      delay(300);
    }
    else
    {
      Serial.println("ENABLE PING DISTANCE FIRST !");
    }
  }
  else if(a.indexOf("SHOW")==0)
  {
    Serial.println("____________________________________________________________________________");
    for(i=0;i<3;i++)
    {
      for(j=0;j<6;j++)
      {
        Serial.print(park[i][j]);
        Serial.print("\t\t");
      }
      Serial.println();
    }
    Serial.println("____________________________________________________________________________");
  }
  else if(a.indexOf("SAVE")==0)
  {
    saveToRom(1);
    Serial.println("Saved !");
  }
  else if(a.indexOf("RESET")==0)
  {
    saveToRom(0);
    loadFromRom();
    Serial.println("Reset !");
  }
  else if(a.indexOf("ACTIVATE")==0)
  {
    initexe(1);
  }
  else if(a.indexOf("DEACTIVATE")==0)
  {
    initexe(0);
  }
  else
  {
    invalid();
  }
}

void invalid()
{
  Serial.println("INVALID COMMAND !");
}

void initexe(int x)
{
  if(x==1)
  {
    for(i=0;i<6;i++)
    {
      o[i]='N';
    }
    Serial.println("Starting execution ...");
    Serial.println(o[0]);
    Serial.println(o[1]);
    Serial.println(o[2]);
    Serial.println(o[3]);
    Serial.println(o[4]);
    Serial.println(o[5]);
    active=1;
  }
  else if(x==0)
  {
    active=0;
    Serial.println("Stopping execution ...");
  }
}

void simulate()
{
  for(i=0;i<6;i++)
  {
    j=park[0][i];
    if(j==-1)
    {
      continue; 
    }
    ld=readL();
    Serial.println("Check");
    if(ld>park[2][i]&&ld<park[1][i])
    {
      o[i]='1';
    }
    else
    {
      o[i]='0';
    }
    Serial.println(o);
  }
  //Serial.println("Check");
//  String xyz=o[0]+" "+o[1]+" "+o[2]+" "+o[3]+" "+o[4]+" "+o[5];
  //Serial.println(o[0]);
}

int check(int a)
{
  if(a==11||a==12||a==21||a==22||a==31||a==32||a==42||a==42||a==52||a==52||a==62||a==62)
  {
    return a;
  }
  return -1;
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

float readL()
{
  long duration, inches;
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  return (float)(duration*0.017);
}

void pingdistance()
{
  val=readL();
  Serial.println(val);
  delay(100);
}

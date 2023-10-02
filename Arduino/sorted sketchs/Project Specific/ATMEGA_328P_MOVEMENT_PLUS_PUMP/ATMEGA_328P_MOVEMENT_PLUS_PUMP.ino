int i;

int PUMP_IN=7;
int RELAYLF=2;
int RELAYLB=4;
int RELAYRF=5;
int RELAYRB=6;

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
}

void pinsetup()
{
  pinMode(PUMP_IN,OUTPUT);
  pinMode(RELAYLF,OUTPUT);
  pinMode(RELAYLB,OUTPUT);
  pinMode(RELAYRF,OUTPUT);
  pinMode(RELAYRB,OUTPUT);
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
}

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  //Serial.println(m);
  if(m=="")
  {
    return;
  }
  Serial.println(cmd(m));
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
    moveLeft();
  }
  else if(a==2)
  {
    moveRight();
  }
  else if(a==3)
  {
    moveForward();
  }
  else if(a==4)
  {
    moveBackward();
  }
}

void stopMoving()
{
  digitalWrite(PUMP_IN,HIGH);
  digitalWrite(RELAYLF,HIGH);
  digitalWrite(RELAYLB,HIGH);
  digitalWrite(RELAYRF,HIGH);
  digitalWrite(RELAYRB,HIGH);
}

void moveLeft()
{
  digitalWrite(RELAYLF,HIGH);
  digitalWrite(RELAYLB,LOW);
  digitalWrite(RELAYRF,LOW);
  digitalWrite(RELAYRB,HIGH);
}

void moveRight()
{
  digitalWrite(RELAYLF,LOW);
  digitalWrite(RELAYLB,HIGH);
  digitalWrite(RELAYRF,HIGH);
  digitalWrite(RELAYRB,LOW);
}

void moveForward()
{
  digitalWrite(RELAYLF,LOW);
  digitalWrite(RELAYLB,HIGH);
  digitalWrite(RELAYRF,LOW);
  digitalWrite(RELAYRB,HIGH);
}

void moveBackward()
{
  digitalWrite(RELAYLF,HIGH);
  digitalWrite(RELAYLB,LOW);
  digitalWrite(RELAYRF,HIGH);
  digitalWrite(RELAYRB,LOW);
}

//pump function
void wPump(boolean a)
{
  if(a)
  {
    digitalWrite(PUMP_IN,LOW);
  }
  else
  {
    digitalWrite(PUMP_IN,HIGH);
  }
}

int i;

int PLUS=2;
int RELAYLP=5;
int RELAYLN=6;
int RELAYRP=7;
int RELAYRN=8;

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
  pinMode(PLUS,OUTPUT);
  pinMode(RELAYLP,OUTPUT);
  pinMode(RELAYLN,OUTPUT);
  pinMode(RELAYRP,OUTPUT);
  pinMode(RELAYRN,OUTPUT);
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
    //initState();
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
  digitalWrite(PLUS,HIGH);
  digitalWrite(RELAYLP,HIGH);
  digitalWrite(RELAYLN,HIGH);
  digitalWrite(RELAYRP,HIGH);
  digitalWrite(RELAYRN,HIGH);
}

void moveLeft()
{
  digitalWrite(PLUS,LOW);
  digitalWrite(RELAYLP,LOW);
  digitalWrite(RELAYLN,LOW);
  digitalWrite(RELAYRP,HIGH);
  digitalWrite(RELAYRN,HIGH);
}

void moveRight()
{
  digitalWrite(PLUS,LOW);
  digitalWrite(RELAYLP,HIGH);
  digitalWrite(RELAYLN,HIGH);
  digitalWrite(RELAYRP,LOW);
  digitalWrite(RELAYRN,LOW);
}

void moveForward()
{
  digitalWrite(PLUS,LOW);
  digitalWrite(RELAYLP,HIGH);
  digitalWrite(RELAYLN,HIGH);
  digitalWrite(RELAYRP,HIGH);
  digitalWrite(RELAYRN,HIGH);
}

void moveBackward()
{
  digitalWrite(PLUS,LOW);
  digitalWrite(RELAYLP,LOW);
  digitalWrite(RELAYLN,LOW);
  digitalWrite(RELAYRP,LOW);
  digitalWrite(RELAYRN,LOW);
}

//pump function
void wPump(boolean a)
{
  /*
  if(a)
  {
    digitalWrite(PUMP_IN,LOW);
  }
  else
  {
    digitalWrite(PUMP_IN,HIGH);
  }
  */
}

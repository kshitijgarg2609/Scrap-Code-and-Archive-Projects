int i;

int IN=8; //Pump
int IN1=9; // Left Forward
int IN2=10; // Left Backward

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
  pinMode(IN,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
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
    MoveLeft();
  }
  else if(a==2)
  {
    MoveRight();
  }
  else if(a==3)
  {
    MoveForward();
  }
}

void stopMoving()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
}

void MoveLeft()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void MoveRight()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void MoveForward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

//pump function
void wPump(boolean a)
{
  if(a)
  {
    digitalWrite(IN,LOW);
  }
  else
  {
    digitalWrite(IN,HIGH);
  }
}

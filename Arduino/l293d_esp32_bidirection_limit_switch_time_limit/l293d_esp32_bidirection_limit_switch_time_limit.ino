int limit_u=32;
int limit_d=33;
int motor_u=25;
int motor_d=26;

long snp=0;
long timeout=10000;
int motor_dir=0;

int lst_u=0;
int lst_d=0;

void setup()
{
  Serial.begin(115200);
  pinMode(limit_u,INPUT_PULLUP);
  pinMode(limit_d,INPUT_PULLUP);
  pinMode(motor_u,OUTPUT);
  pinMode(motor_d,OUTPUT);
}

void loop()
{
  serialEvent();
  processMotorStop();
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
  if(m=="")
  {
    return;
  }
  Serial.println(m);
  cmd(m);
}

void cmd(String a)
{
  if(a.equals("up"))
  {
    startUpward();
  }
  else if(a.equals("down"))
  {
    startDownward();
  }
  else if(a.equals("stop"))
  {
    stopMotor();
  }
}

void processMotorStop()
{
  if(motor_dir==0)
  {
    return;
  }
  int nxt=0;
  if(motor_dir==1)
  {
    nxt=digitalRead(limit_u);
    if(nxt==lst_u && lst_u==0)
    {
      //Serial.println("LIMIT STOP");
      stopMotor();
      return;
    }
    lst_u=nxt;
  }
  if(motor_dir==2)
  {
    nxt=digitalRead(limit_d);
    if(nxt==lst_d && lst_d==0)
    {
      //Serial.println("LIMIT STOP");
      stopMotor();
      return;
    }
    lst_d=nxt;
  }
  if((millis()-snp)>=timeout)
  {
    stopMotor();
  }
}

void startUpward()
{
  stopMotor();
  snp=millis();
  digitalWrite(motor_u,HIGH);
  digitalWrite(motor_d,LOW);
  motor_dir=1;
  lst_u=1;
}

void startDownward()
{
  stopMotor();
  snp=millis();
  digitalWrite(motor_u,LOW);
  digitalWrite(motor_d,HIGH);
  motor_dir=2;
  lst_d=1;
}

void stopMotor()
{
  motor_dir=0;
  digitalWrite(motor_u,LOW);
  digitalWrite(motor_d,LOW);
}

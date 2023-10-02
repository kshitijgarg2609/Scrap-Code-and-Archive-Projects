int limit_u=34;
int limit_d=35;
int motor_u=25;
int motor_d=26;

int motor_dir=0;

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

void startUpward()
{
  stopMotor();
  digitalWrite(motor_u,HIGH);
  digitalWrite(motor_d,LOW);
  motor_dir=1;
}

void startDownward()
{
  stopMotor();
  digitalWrite(motor_u,LOW);
  digitalWrite(motor_d,HIGH);
  motor_dir=2;
}

void stopMotor()
{
  motor_dir=0;
  digitalWrite(motor_u,LOW);
  digitalWrite(motor_d,LOW);
}

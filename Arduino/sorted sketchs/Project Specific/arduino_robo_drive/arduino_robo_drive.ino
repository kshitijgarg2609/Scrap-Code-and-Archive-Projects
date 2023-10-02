int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;

void setup()
{
  Serial.begin(115200);
  pinConfig();
}

void pinConfig()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  stopMoving();
}

void loop()
{
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
  if((a.length()==4)&&(a.indexOf("op:")!=-1))
  {
    char c=a.charAt(3);
    if(c>='0'&&c<='5')
    {
      operation(c-'0');
      return "1";
    }
    return "0";
  }
  return "0";
}

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
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void moveLeft()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void moveRight()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void moveForward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void moveBackward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

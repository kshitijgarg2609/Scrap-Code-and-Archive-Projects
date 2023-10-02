int trig1=D1;
int echo1=D2;
int trig2=D6;
int echo2=D5;

void setup()
{
  Serial.begin(115200);
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
}

void loop()
{
  Serial.println(String(readUltrasonic('1',trig1,echo1))+"\t"+String(readUltrasonic('1',trig2,echo2)));
  delay(500);
}

String readUltrasonic(char a,int trig,int echo)
{
  float dis;
  long duration;
  if(a=='1')
  {
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duration=pulseInLong(echo,HIGH);
    dis=duration*0.017;
    dis=(dis>=2&&dis<=200)?dis:(-1);
    return "("+String(dis)+" cm)";
  }
  else if(a=='0')
  {
    return "(#0)";
  }
  return "(#)";
}

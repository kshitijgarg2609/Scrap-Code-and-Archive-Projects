int x=-1;
int flg=0;
String str="";


void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  analogWrite(11,0);
}

void loop()
{
x=-1;
flg=0;
str="";  
while(Serial.available()>0)
{
  flg=1;
  str+=char(Serial.read());
  delay(250);
}
Serial.flush();
  if(flg==1)
  {
    x=str.toInt();
  }
if(x>=0&&x<=255)
  {
    char buf[11];
    analogWrite(11,x);
    sprintf(buf,"Brightness : %d",x);
    Serial.println(buf);
  }
  else if(x!=-1)
  {
    Serial.println("Input Error!");
  }
}

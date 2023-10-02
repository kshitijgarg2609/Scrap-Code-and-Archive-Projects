void setup() {
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
}

void loop()
{
  for(int i=0;i<255;i+=4)
  {
    analogWrite(10,i);
    analogWrite(11,255-i);
    delay(20);
  }
}

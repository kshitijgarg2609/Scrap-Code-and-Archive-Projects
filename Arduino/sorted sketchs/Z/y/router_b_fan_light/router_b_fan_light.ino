
void setup() {
  // put your setup code here, to run once:
pinMode(8,INPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
//Serial.begin(9600);
}

void loop()
{
  if(digitalRead(8)==HIGH)
  {
  //  Serial.println("Fan ON");
    analogWrite(9,255);
    analogWrite(10,255);
  }
  else
  {
    //Serial.println("Fan OFF");
    analogWrite(9,0);
    analogWrite(10,0);
  }
  //delay(100);
}

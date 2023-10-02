int lt=2;//left
int rt=3;//right
int sgnl=A3;//signal

void setup()
{
  Serial.begin(9600);
  pinMode(lt,INPUT);
  pinMode(rt,INPUT);
  digitalWrite(lt,LOW);
  digitalWrite(rt,LOW);
}

void loop()
{
  if(digitalRead(lt)==LOW&&digitalRead(rt)==LOW)
  {
    Serial.println(analogRead(sgnl));
  }
  delay(1);
}

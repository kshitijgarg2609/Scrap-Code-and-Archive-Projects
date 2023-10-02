int r;
int p = A0;
float v;
float ntu;

void setup()
{
  Serial.begin(9600);
  pinMode(p, INPUT);
}

void loop()
{
  r = analogRead(p);
  v = ((r / 1024.0) * 5.0);
  //ntu = -1120.4*square(r)+(1024*5742.3)*r-(1048576*4353.8);
  //ntu = -1120.4*square(r)+(1024*5742.3)*r-(1048576*4353.8);
  ntu = -1120.4 * square(v) + 5742.3 * v - 4353.8;
  //ntu/=1048576;
  Serial.println(r);
  //Serial.println(v);
  //Serial.println("check");
  //Serial.println(ntu);
  //delay(300);
}

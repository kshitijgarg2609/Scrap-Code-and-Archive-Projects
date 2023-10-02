int a,b;
String o;
float va,vb;

void setup()
{
  Serial.begin(9600);
  //pinMode(2,INPUT);
  //pinMode(3,INPUT);
}

void loop()
{
  a=analogRead(A0);
  //b=analogRead(A1);
  //va=(a*5)/1024.0;
  //vb=(b*5)/1024.0;
  //o=String(a)+" "+String(b);
  Serial.println(a);
  //Serial.print(":");
  //Serial.print(va);
  ///Serial.print(" :: ");
  //Serial.print(b);
  //Serial.print(":");
  //Serial.print(vb);
  //Serial.println();
  //delay(500);
}

int i=0;

void setup()
{
pinMode(11,OUTPUT);
}

void loop()
{
for(i=0;i<256;i+=20)
{
analogWrite(11,i);
delay(1000);
}
}

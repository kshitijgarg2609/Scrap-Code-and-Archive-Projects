const int pin1 = A0;
const int pin2 = 5;

void setup()
{
pinMode(pin1,OUTPUT);
pinMode(pin2,INPUT);
Serial.print("BomB Set");
Serial.begin(9600);
}

void loop()
{
if(digitalRead(pin2) == HIGH)
{
Serial.println("\n Bomb Working\n");
delay(500);
}
else
{
Serial.println("\n BOMB DIFFUSED \n");  
}
delay(500);
}

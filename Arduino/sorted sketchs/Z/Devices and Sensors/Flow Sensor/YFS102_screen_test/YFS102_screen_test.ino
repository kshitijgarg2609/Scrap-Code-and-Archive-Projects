#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);

float f,r=0;

int p=3;

void setup()
{
  lcd.begin();
  Serial.begin(9600);
  pinMode(p,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),measure,LOW);
}

void loop()
{
  setLCD();
}

String com(String str,int tspace)
{
  int i,j;
  i=tspace-str.length();
  for(j=1;j<=i;j++)
  {
    str+=" ";
  }
  return str;
}

void setLCD()
{
  delay(4);
  lcd.setCursor(4,0);
  delay(4);
  lcd.print(com(String(r),10)+" L/m"); 
}

void measure()
{
  f=pulseIn(p,HIGH)+pulseIn(p,LOW);
  if(f!=0)
  {
    f=1000000.0/f;
  }
  r=f/7.5;
  //setLCD();
  Serial.println(r);
}

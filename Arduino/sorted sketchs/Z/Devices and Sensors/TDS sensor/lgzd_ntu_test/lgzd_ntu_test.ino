//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorPin = A0;
float volt;
float ntu;
 
void setup()
{
  Serial.begin(9600);
  //lcd.begin();
 
  // Turn on the blacklight and print a message.
  //lcd.backlight();
}
 
void loop()
{
    
    volt = 0;
    for(int i=0; i<1; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt;///800;
    //volt = round_to_dp(volt,1);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
      ntu+=195;
    }
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(volt);
    //lcd.print(" V");
 
    //lcd.setCursor(0,1);
    //lcd.print(ntu);
    //lcd.print(" NTU");
    Serial.println(volt);
    Serial.println(ntu);
    delay(1000);
}
 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

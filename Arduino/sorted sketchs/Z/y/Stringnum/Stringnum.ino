#include <EEPROM.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
String a="123";
String b="mov 456";
int x=a.toInt();  
Serial.println(x);
int y=b.toInt();
Serial.println(y);
char z;
EEPROM.get(0,z);
Serial.println(z);
for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, -1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

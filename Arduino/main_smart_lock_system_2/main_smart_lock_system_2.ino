#include <SPI.h>
#include <MFRC522.h>
#include <RTClib.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>

#include <Stepper.h>

#define OLED_ADDR  0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define SS_PIN 10
#define RST_PIN 9

Adafruit_SSD1306 oled1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
MFRC522 rfid1(SS_PIN, RST_PIN);
DS3231 rtc1;
//#################################################################################

DateTime dt1;
Stepper sm(32, 5,6,7,8);

void setup()
{
  SPI.begin();
  Wire.begin();
  rfid1.PCD_Init();
  oled1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  rtc1.begin();
  Serial.begin(115200);
  oled1.clearDisplay();
  oled1.display();
  sm.setSpeed(1200);
}

void loop()
{
  readRFID();
}

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  cmd(m);
}

void cmd(String a)
{
  if(a.equals("request"))
  {
    char fetch[100]="DD-MM-YYYY hh:mm:ss";
    dt1=rtc1.now();
    dt1.format(fetch);
    Serial.println("current:"+String(fetch));
  }
  else if(a.length()==23&&a.indexOf("set:")!=-1)
  {
    dt1=DateTime(a.substring(4,14).c_str(),a.substring(15).c_str());
    rtc1.adjust(dt1);
    Serial.println("set time");
  }
}
//Functionality
void openGate(String a)
{
  displayOLED(a);
  a=requestRTC()+", "+a;
  Serial.println("DATALOG:"+a);
  sm.step(2048);
}

void closeGate()
{
  sm.step(-2048);
}
//###################OLED######################

void clearOLED()
{
  oled1.clearDisplay();
  oled1.display();
}

void displayOLED(String a)
{
  oled1.clearDisplay();
  oled1.setTextSize(2);
  oled1.setTextColor(WHITE);
  oled1.setCursor(0,0);
  oled1.print(a);
  oled1.display();
}

//################RFID########################
void readRFID()
{
  if (!rfid1.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid1.PICC_ReadCardSerial())
  {
    return;
  }
  String uid_str=readUID();
  //Serial.println(uid_str);
  openGate(uid_str);
  delay(3000);
  closeGate();
}

String readUID()
{
  char rfid_str[8];
  sprintf(rfid_str,"%02x%02x%02x%02x",rfid1.uid.uidByte[0],rfid1.uid.uidByte[1],rfid1.uid.uidByte[2],rfid1.uid.uidByte[3]);
  return String(rfid_str);
}
//##########################RTC####################

String requestRTC()
{
  char fetch[]="YYYY_MM_DD_hh_mm_ss";
  dt1=rtc1.now();
  dt1.format(fetch);
  return String(fetch);
}

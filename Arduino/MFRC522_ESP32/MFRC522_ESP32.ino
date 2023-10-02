#include <SPI.h>
#include <MFRC522.h>

//#define SS_PIN 9
#define RST_PIN 34
 
MFRC522 rfid(4);

void setup()
{
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}

void loop()
{
  readRFID();
}

void readRFID()
{
  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }
  String uid_str=readUID();
  Serial.println(uid_str);
}

String readUID()
{
  String tmp="";
  for(int i=0;i<4;i++)
  {
    int byt=rfid.uid.uidByte[i];
    int fh=hexChar(byt/16);
    int lh=hexChar(byt%16);
    tmp=tmp+(char)(fh)+(char)(lh);
  }
  return tmp;
}

char hexChar(int a)
{
  if(a>=0&&a<10)
  {
    return (char)(a+'0');
  }
  else if(a>=10&&a<16)
  {
    return (char)(a-10+'A');
  }
  else
  {
    return ' ';
  }
}

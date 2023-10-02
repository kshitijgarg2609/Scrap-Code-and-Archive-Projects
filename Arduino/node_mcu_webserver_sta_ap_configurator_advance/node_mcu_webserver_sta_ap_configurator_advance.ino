#include "WiFiModuleEEPROM.h"

void setup()
{
  Serial.begin(115200);
  initProcess(true);
}

void loop()
{
  confProcess();
}

#include "camera_frame_data1.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("check serial");
  initCam1();
}

void loop()
{
  if(getFrame1()==1)
  {
    Serial.println("FRAME");
  }
  else
  {
    Serial.println("NOT FRAME");
  }
}

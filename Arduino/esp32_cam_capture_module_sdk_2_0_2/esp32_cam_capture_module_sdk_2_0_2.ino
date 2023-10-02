#include "camera_frame_data.h"

void setup()
{
  Serial.begin(115200);
  initCam(true);
}

void loop()
{
  if(getFrame()==1)
  {
    Serial.println("frame : "+String(framecam->len));
  }
  else
  {
    Serial.println("frame error");
  }
}

void setup()
{
  Serial.begin(115200);
  initCam();
}

void loop()
{
  if(getFrame())
  {
    Serial.println("FRAME CAPTURED !!!");
  }
  else
  {
    Serial.println("FRAME ERROR !!!");
  }
}

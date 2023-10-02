String ntu;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  ntu=getNTU();
  Serial.println(ntu);
  delay(1000);
}

String getNTU()
{
  float vol=((float)analogRead(A0)/1024.0)*5.0;
  float fntu=-1120.4*square(vol)+5742.3*vol-4353.8;
  fntu+=180;
  if(fntu>0&&fntu<=3000)
  {
    return String(fntu)+" ntu";
  }
  else
  {
    return "err";
  }
}

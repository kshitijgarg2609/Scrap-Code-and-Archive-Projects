void initPin();

int sensor_ht_pin=10;
int fpin=D0;

int rtc_rst=9;
int rtc_dat=D9;
int rtc_clk=D10;

int pb_pin[6];

void initPin()
{
  pb_pin[0]=D1;
  pb_pin[1]=D2;
  pb_pin[2]=D3;
  pb_pin[3]=D5;
  pb_pin[4]=D6;
  pb_pin[5]=D7;

  for(int i=0;i<6;i++)
  {
    pinMode(pb_pin[i],INPUT_PULLUP);
    digitalWrite(pb_pin[i],HIGH);
  }
  pinMode(fpin,OUTPUT);
}

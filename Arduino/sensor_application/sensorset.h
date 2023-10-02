#include <Adafruit_Sensor.h>
#include <DHT.h>

int led1_pin=4;
int led2_pin=5;
int dht_pin=6;
int sensor_trig=8;
int sensor_echo=9;
int sensor_soil_moisture=A0;

DHT dht(dht_pin,DHT11);

void pinSet();
String sensor();
String readDHT();
String readUltrasonic();
String readSoilMoisture();

void pinSet()
{
  pinMode(led1_pin,OUTPUT);
  pinMode(led2_pin,OUTPUT);
  dht.begin();
  pinMode(sensor_trig,OUTPUT);
  pinMode(sensor_echo,INPUT);
}

String sensor()
{
  return (readDHT()+"#"+readUltrasonic()+"#"+readSoilMoisture());
}

String readDHT()
{
  float tem,hum;
  tem = dht.readTemperature();
  hum = dht.readHumidity();
  if (isnan(tem) || isnan(hum))
  {
    return "!#!";
  }
  return String(tem)+"#"+String(hum);
}

String readUltrasonic()
{
  digitalWrite(sensor_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_trig,LOW);
  int duration=pulseIn(sensor_echo,HIGH);
  float dis=duration*0.017;
  dis=(dis>=2&&dis<=200)?dis:(-1);
  return String(dis);
}

String readSoilMoisture()
{
  float i=analogRead(sensor_soil_moisture);
  return String(1/1023);
}

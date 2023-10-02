#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Servo.h>

DHT dht(4,DHT11);

Servo a;
Servo b;
Servo c;
Servo d;
Servo e;

int f=12;
int g=13;
int h=A1;
int i=A2;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  a.attach(5);
  b.attach(6);
  c.attach(9);
  d.attach(10);
  e.attach(11);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
}

void loop() {
  // Delay between measurements.
  delay(1000);
  float t = dht.readTemperature();
  Serial.println(String(t));
  
  a.write(80);
  b.write(80);
  c.write(80);
  d.write(80);
  e.write(80);
  
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(h,HIGH);
  digitalWrite(i,HIGH);

  delay(1000);

  a.write(100);
  b.write(100);
  c.write(100);
  d.write(100);
  e.write(100);

  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(h,LOW);
  digitalWrite(i,LOW);
  
}

#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

Servo sv;

int deg[6];
int len[6];
int park[6];

void setup()
{
int i;
for(i=0;i<6;i++)
{
park[i]=0;
}
deg[0]=50;
deg[1]=64;
deg[2]=80;
deg[3]=100;
deg[4]=116;
deg[5]=130;
len[0]=13;
len[1]=12;
len[2]=10;
len[3]=10;
len[4]=12;
len[5]=13;
sv.attach(9);
sv.write(90);
Serial.begin(9600); // Starting Serial Terminal
}

void loop()
{
int i;
int read;
for(i=0;i<6;i++)
{
sv.write(deg[i]);
read=readL();
if(ranger(i,read)==1)
{
park[i]=0;
}
else
{
park[i]=1;
}
delay(100);
}
printpark();
}

int ranger(int i,int r)
{
int a,b;
a=len[i]-1;
b=len[i]+1;
if(i==0||i==6)
{
a=len[i]-2;
b=len[i]+2;  
}
if(r>=a&&r<=b)
{
return 1;
}
return 0;
}

int readL()
{
long duration, inches, cm;
pinMode(pingPin, OUTPUT);
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
cm = microsecondsToCentimeters(duration);
return (int)cm;
}

void printpark()
{
int i;
for(i=0;i<6;i++)
{
Serial.print(park[i]);
}
Serial.print("\n");
}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}

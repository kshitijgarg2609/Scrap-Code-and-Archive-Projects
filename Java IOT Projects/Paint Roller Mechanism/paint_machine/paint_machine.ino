#include "E2PROMConf.h"
#include <Servo.h>
#include "paint_pins.h"

//Main Process
boolean run_process=false;
boolean nozzle_flg=false;
boolean phase_flg=false;
boolean sub_process=false;
boolean paint_process=false;
boolean motor_resumer=false;

boolean cut_flg=false;
//Motor
unsigned long motor_snp=0;
boolean motor_flg=false;

//Sensor
uint32_t cnt=0;
uint32_t rot=0;
uint32_t r_count=0;
boolean round_flg=false;
boolean high_flg=false;

boolean sensor_flg=false;
unsigned long read_snp=0;

//Brakes
Servo serv;
boolean brake_flg=false;
long brake_snp=0;

//Serial IO

void setup()
{
  Serial.begin(115200);
  digitalWrite(cut_pin,HIGH);
  digitalWrite(nozzle_pin,HIGH);
  pinMode(esp,OUTPUT);
  analogWrite(esp,166);
  beginMotor();
  beginOpto();
  initDefault();
  initBrake();
}

void loop()
{
  processHandle();
  motorProcess();
  //sensorReadProcess();
  brakeProcess();
}

//Main Process
void startProcess()
{
  stopProcess();
  run_process=true;
}

void stopProcess()
{
  motor_resumer=false;
  phase_flg=false;
  run_process=false;
  sub_process=false;
  stopMotor();
  nozzlePaint(false);
  brakeRelease();
}

void interruptProcess()
{
  Serial.println("PROCESS INTERRUPTED");
  stopProcess();
}

void processHandle()
{
  if(run_process)
  {
    if(!sub_process)
    {
      nozzlePaint(true);
      motor_resumer=true;
      resetCnt();
      phase_flg=true;
      sub_process=true;
      continousLeft();
    }
  }
}

void subProcessHandle()
{
  if(!sub_process)
  {
    return;
  }
  if(nozzle_flg)
  {
    if(cnt>=obj.opto_count)
    {
      nozzlePaint(false);
    }
  }
  else if(!nozzle_flg)
  {
    if(phase_flg&&cnt>obj.phase_count)
    {
      applyBrake();
      cut();
      phase_flg=false;
      Serial.println("Excecuted !!!");
    }
    if(!phase_flg&&cnt>=obj.round_cut)
    {
      sub_process=false;
    }
  }
}

void nozzlePaint(boolean a)
{
  nozzle_flg=a;
  if(a)
  {
    digitalWrite(nozzle_pin,LOW);
    Serial.println("NOZZLE ON");
  }
  else
  {
    digitalWrite(nozzle_pin,HIGH);
    Serial.println("NOZZLE OFF");
  }
}

void cut()
{
  Serial.println("ROUND CUT");
  cut_flg=true;
  digitalWrite(cut_pin,LOW);
  //delay(500);
}


//Motor

void beginMotor()
{
  pinMode(motor_speed_pin,OUTPUT);
  pinMode(motor_d1,OUTPUT);
  pinMode(motor_d2,OUTPUT);
  stopMotor();
}

void operateLeft(uint8_t a)
{
  motor_snp=millis();
  motor_flg=true;
  analogWrite(motor_speed_pin,a);
  digitalWrite(motor_d1,HIGH);
  digitalWrite(motor_d2,LOW);
}

void continousLeft()
{
  analogWrite(motor_speed_pin,obj.motor_speed);
  digitalWrite(motor_d1,HIGH);
  digitalWrite(motor_d2,LOW);
}

void operateRight(uint8_t a)
{
  motor_snp=millis();
  motor_flg=true;
  analogWrite(motor_speed_pin,a);
  digitalWrite(motor_d1,LOW);
  digitalWrite(motor_d2,HIGH);
}

void motorProcess()
{
  if(motor_flg&&(millis()-motor_snp)>=1000)
  {
    stopMotor();
  }
}

void stopMotor()
{
  motor_flg=false;
  analogWrite(motor_speed_pin,0);
  digitalWrite(motor_d1,HIGH);
  digitalWrite(motor_d2,HIGH);
}

//Sensor
void resetCnt()
{
  cnt=0;
  rot=0;
  r_count=0;
  Serial.println("SENSOR COUNT RESET");
}

void beginOpto()
{
  attachInterrupt(digitalPinToInterrupt(opto_sensor_pin),processHighLow,CHANGE);
}

/*
void sensorReadProcess()
{
  if(sensor_flg&&(millis()-read_snp)>=10000)
  {
    sensor_flg=false;
    Serial.println("SENSOR TIMEOUT");
    if(run_process)
    {
      interruptProcess();
      return;
    }
    resetCnt();
  }
}

void notifySensor()
{
  read_snp=millis();
  sensor_flg=true;
}
*/

void processHighLow()
{
  //notifySensor();
  if(high_flg&&digitalRead(opto_sensor_pin)==HIGH)
  {
    subProcessHandle();
    counter();
    high_flg=false;
  }
  if(!high_flg&&digitalRead(opto_sensor_pin)==LOW)
  {
    high_flg=true;
  }
}

void counter()
{
  cnt++;
  if((cnt%obj.opto_count)==0)
  {
    rot++;
    Serial.println("TOTAL ROTATIONS :- "+String(rot));
  }
  else
  {
    Serial.println("COUNT :- "+String(cnt));
  }
}
//Brakes
void initBrake()
{
  serv.attach(brake_pin);
  brakeRelease();
}

void brakePress()
{
  serv.write(obj.brake_angle);
}

void brakeRelease()
{
  serv.write(obj.brake_init_angle);
  if(cut_flg==true)
  {
    digitalWrite(cut_pin,HIGH);
    cut_flg=false;
  }
}

void brakeProcess()
{
  if(brake_flg&&((millis()-brake_snp)>=2000))
  {
    brakeRelease();
    brake_flg=false;
    Serial.println("BRAKES RELEASED !!!");
    if(motor_resumer)
    {
      continousLeft();
      motor_resumer=false;
    }
  }
}

void applyBrake()
{
  stopMotor();
  brake_snp=millis();
  brakePress();
  brake_flg=true;
  Serial.println("BRAKES APPLIED !!!");
}

//Serial IO

void cmd(String a)
{
  uint8_t op_spd=0;
  if(a.equals("echo"))
  {
    Serial.println("DEVICE ONLINE");
  }
  else if(a.equals("start process"))
  {
    Serial.println("PROCESS STARTING ...");
    startProcess();
  }
  else if(a.equals("stop process"))
  {
    Serial.println("PROCESS STOPPING ...");
    stopProcess();
  }
  else if(a.indexOf("left:")!=-1)
  {
    op_spd=(uint8_t)(a.substring(5).toInt()%256);
    operateLeft(op_spd);
  }
  else if(a.indexOf("right:")!=-1)
  {
    op_spd=(uint8_t)(a.substring(6).toInt()%256);
    operateRight(op_spd);
  }
  else if(a.equals("idle run motor"))
  {
    continousLeft();
  }
  else if(a.indexOf("stop")!=-1)
  {
    stopMotor();
  }
  else if(a.equals("brake"))
  {
    applyBrake();
  }
  else if(a.equals("erase"))
  {
    eraseData();
  }
  else if(a.indexOf("set")!=-1)
  {
    Serial.println(setCmd(a));
  }
  else if(a.indexOf("get")!=-1)
  {
    Serial.println(getCmd(a));
  }
  else
  {
    Serial.println("INVALID COMMAND");
  }
}

//Serial Operation

void serialEvent()
{
  String m="";
  char c='\0';
  while(Serial.available()>0)
  {
    delay(1);
    c=Serial.read();
    if(c=='\n'||c=='\r')
    {
      continue;
    }
    m+=c;
  }
  if(m=="")
  {
    return;
  }
  cmd(m);
}

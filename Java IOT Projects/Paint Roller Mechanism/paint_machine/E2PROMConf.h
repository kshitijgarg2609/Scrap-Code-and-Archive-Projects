#include <EEPROM.h>

uint8_t project_code=(uint8_t)('P');
//Variables
typedef struct edata
{
  char code;
  uint8_t motor_speed;
  uint16_t opto_count;
  uint16_t phase_count;
  uint16_t round_cut;
  uint8_t brake_init_angle;
  uint8_t brake_angle;
}edata;

edata obj;
edata dflt;

//definitions
void initDefault();
String setCmd(String);
String getCmd(String);
void eraseData();
void updateObject();
void setMotorSpeed(int);
void setOptoCount(int);
void setPhaseCount(int);
void setRoundCut(int);
void setBrakeInitAngle(int);
void setBrakeAngle(int);

void initDefault()
{
  uint8_t chk;
  dflt.code=project_code;
  dflt.motor_speed=120;
  dflt.opto_count=8;
  dflt.phase_count=30;
  dflt.round_cut=40;
  dflt.brake_init_angle=180;
  dflt.brake_angle=90;
  EEPROM.get(0,chk);
  if(chk!=project_code)
  {
    EEPROM.put(0,dflt);
    Serial.println("DEVICE SET TO DEFAULT");
  }
  EEPROM.get(0,obj);
}

String setCmd(String a)
{
  int colon_indx=a.indexOf(':');
  if(colon_indx==-1)
  {
    return "INVALID COMMAND";
  }
  String basic_cmd=a.substring(0,colon_indx);
  if(basic_cmd.equals("set#motor_speed"))
  {
    setMotorSpeed(a.substring(colon_indx+1).toInt());
    return "MOTOR SPEED SET : "+String(obj.motor_speed);
  }
  else if(basic_cmd.equals("set#opto_count"))
  {
    setOptoCount(a.substring(colon_indx+1).toInt());
    return "OPTO COUNT SET : "+String(obj.opto_count);
  }
  else if(basic_cmd.equals("set#phase_count"))
  {
    setPhaseCount(a.substring(colon_indx+1).toInt());
    return "PHASE COUNT SET : "+String(obj.phase_count);
  }
  else if(basic_cmd.equals("set#round_cut"))
  {
    setRoundCut(a.substring(colon_indx+1).toInt());
    return "ROUND CUT SET : "+String(obj.round_cut);
  }
  else if(basic_cmd.equals("set#brake_init_angle"))
  {
    setBrakeInitAngle(a.substring(colon_indx+1).toInt());
    return "BRAKE INIT ANGLE SET : "+String(obj.brake_init_angle);
  }
  else if(basic_cmd.equals("set#brake_angle"))
  {
    setBrakeAngle(a.substring(colon_indx+1).toInt());
    return "Brake Angle SET : "+String(obj.brake_angle);
  }
  else
  {
    return "INVALID COMMAND";
  }
}

String getCmd(String a)
{
  if(a.equals("get#motor_speed"))
  {
    return "MOTOR SPEED : "+String(obj.motor_speed);
  }
  else if(a.equals("get#opto_count"))
  {
    return "OPTO COUNT : "+String(obj.opto_count);
  }
  else if(a.equals("get#phase_count"))
  {
    return "PHASE COUNT : "+String(obj.phase_count);
  }
  else if(a.equals("get#round_cut"))
  {
    return "ROUND CUT : "+String(obj.round_cut);
  }
  else if(a.equals("get#brake_init_angle"))
  {
    return "BRAKE INIT ANGLE : "+String(obj.brake_init_angle);
  }
  else if(a.equals("get#brake_angle"))
  {
    return "BRAKE ANGLE : "+String(obj.brake_angle);
  }
  else
  {
    return "INVALID COMMAND";
  }
}

void updateObject()
{
  EEPROM.put(0,obj);
}

void eraseData()
{
  EEPROM.put(0,dflt);
  EEPROM.get(0,obj);
  Serial.println("DEVICE SET TO DEFAULT");
}

void setMotorSpeed(int a)
{
  if(a>0&&a<=255)
  {
    obj.motor_speed=a;
    updateObject();
  }
}

void setOptoCount(int a)
{
  if(a>0&&a<=999)
  {
    obj.opto_count=a;
    updateObject();
  }
}

void setPhaseCount(int a)
{
  if(a>=0&&a<=obj.round_cut)
  {
    obj.phase_count=a;
    updateObject();
  }
}
void setRoundCut(int a)
{
  if(a>0&&a<=9999)
  {
    obj.round_cut=a;
    updateObject();
  }
}
void setBrakeInitAngle(int a)
{
  if(a>=0&&a<=255)
  {
    obj.brake_init_angle=a;
    updateObject();
  }
}
void setBrakeAngle(int a)
{
  if(a>=0&&a<=255)
  {
    obj.brake_angle=a;
    updateObject();
  }
}

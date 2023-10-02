#include "replyinterface.h"
#include <ArduinoWebsockets.h>
#include "utilpkg.h"
//
String model="ESP8266-12E";
String service="SERVICE :- UART, ADC";

boolean wcon=false;
boolean wscon=false;
boolean dcon=false;
boolean rcon=false;

boolean ping_flg=true;
boolean ping_chk=false;

//PIN DATA
String pin_name[10];
int pstor[10];
char pddr[10];
char pset[10];

void initPinData();
void pinControl(String);

using namespace websockets;
WebsocketsClient clnt;

void onMessageCallback(WebsocketsMessage message)
{
  String msg;
   if(message.isBinary()==true)
   {
       msg=message.data();
    if(msg.charAt(0)=='X'&&msg.charAt(1)==':')
    {
      if(!cnfg)
      {
        msg=msg.substring(2);
      }
      replyToSerial(msg);
      if(udp_flg)
      {
        replyToUdp(msg);
      }
    }
    else if(msg.charAt(0)=='P'&&msg.charAt(1)==':')
      {
        pinControl(msg);
      }
    else if(msg.equals("MODEL"))
    {
      clnt.sendBinary("#:"+model);
    }
    else if(msg.equals("SERVICE"))
    {
      clnt.sendBinary("#:"+service);
    }
   }
   else if(message.isText()==true)
   {
      msg=message.data();
    if(msg.charAt(0)=='S')
    {
      if(cnfg)
      {
        replyBack(msg);
      }
      if(msg.equals("S:DEVICE CONNECTED"))
      {
        dcon=true;
      }
      else if(msg.equals("S:ACCESS DENIED"))
      {
        dcon=false;
      }
      else if(msg.equals("S:REMOTE ONLINE"))
      {
        rcon=true;
        clnt.send("UPDATE OBJECT");
      }
      else if(msg.equals("S:REMOTE OFFLINE"))
      {
        rcon=false;
        clnt.send("UPDATE OBJECT");
      }
      else if(msg.equals("S:REMOTE NOT CONNECTED"))
      {
        rcon=false;
      }
      else if(msg.equals("S:SERVER ONLINE"))
      {
        ping_chk=true;
      }
    }
   }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if(event == WebsocketsEvent::ConnectionOpened)
    {
      wscon=true;
      if(cnfg)
      {
        Serial.println("S:SERVER ONLINE");
      }
      clnt.send(auth_key_str);
    }
    else if(event == WebsocketsEvent::ConnectionClosed)
    {
      wscon=false;
      if(cnfg)
      {
        Serial.println("S:SERVER OFFLINE");
      }
    }
}

void initPinData()
{
  int i;
  for(i=0;i<10;i++)
  {
    pddr[i]='X';
    pset[i]='X';
  }
  pstor[0]=D0;
  pstor[1]=D1;
  pstor[2]=D2;
  pstor[3]=D3;
  pstor[4]=D4;
  pstor[5]=D5;
  pstor[6]=D6;
  pstor[7]=D7;
  pstor[8]=D8;
  pstor[9]=A0;
  pin_name[0]="D0";
  pin_name[1]="D1";
  pin_name[2]="D2";
  pin_name[3]="D3";
  pin_name[4]="D4";
  pin_name[5]="D5";
  pin_name[6]="D6";
  pin_name[7]="D7";
  pin_name[8]="D8";
  pin_name[9]="A0";
}

void pinControl(String a)
{
  int len;
  int pnum;
  int indx;
  unsigned int pval;
  String pstr;
  len=a.length();
  if(len==3&&a.equals("P:#"))
  {
    pstr="P:#";
    for(pnum=0;pnum<10;pnum++)
    {
      pstr+=pddr[pnum];
    }
    pstr+="@";
    for(pnum=0;pnum<10;pnum++)
    {
      pstr+=pset[pnum];
    }
    clnt.sendBinary(pstr);
    return;
  }
  //pin selector
  if(a.charAt(2)=='D'&&(a.charAt(3)>='0'&&a.charAt(3)<='8'))
  {
    indx=a.charAt(3)-'0';
    pnum=pstor[indx];
  }
  else if(a.charAt(2)=='A'&&a.charAt(3)=='0')
  {
    indx=9;
    pnum=pstor[indx];
  }
  else
  {
    clnt.sendBinary("P:PIN INVALID");
    return;
  }
  if(len==4&&a.charAt(4)=='I')
  {
    pinMode(pnum,INPUT);
    pddr[indx]='I';
    clnt.sendBinary("P:"+pin_name[indx]+"SET TO INPUT");
  }
  else if(len==5&&a.charAt(4)=='O')
  {
    pinMode(pnum,OUTPUT);
    pddr[indx]='O';
    clnt.sendBinary("P:"+pin_name[indx]+"SET TO OUTPUT");
  }
  else if(len==5&&a.charAt(4)=='H')
  {
    digitalWrite(pnum,HIGH);
    pset[indx]='H';
    clnt.sendBinary("P:"+pin_name[indx]+"SET TO HIGH");
  }
  else if(len==5&&a.charAt(4)=='L')
  {
    digitalWrite(pnum,LOW);
    pset[indx]='L';
    clnt.sendBinary("P:"+pin_name[indx]+"SET TO LOW");
  }
  else if(len==8&&a.charAt(4)=='A')
  {
    pval=digit3(a.charAt(5),a.charAt(6),a.charAt(7));
    analogWrite(pnum,pval);
    pset[indx]='P';
    clnt.sendBinary("P:"+pin_name[indx]+"SET TO "+a.substring(5));
  }
  else if(len>5&&a.charAt(4)=='R')
  {
    if(len==6&&a.charAt(5)=='D')
    {
      pval=digitalRead(pnum);
      clnt.sendBinary("P:"+pin_name[indx]+((pval==HIGH)?":HIGH":":LOW"));
    }
    else if(len==6&&a.charAt(5)=='A')
    {
      pval=analogRead(pnum);
      clnt.sendBinary("P:"+pin_name[indx]+":"+zeroAppend(pval,(indx==9)?4:3));
    }
    else if(len>6&&a.charAt(5)=='P')
    {
      if(a.charAt(6)=='H')
      {
        if(len>=9&&a.charAt(7)=='T')
        {
          pval=pulseIn(pnum,HIGH,digitTime(a.substring(8)));
        }
        else
        {
          pval=pulseIn(pnum,HIGH);
        }
        clnt.sendBinary("P:"+pin_name[indx]+":"+String(pval));
      }
      else if(a.charAt(6)=='L')
      {
        if(len>=9&&a.charAt(7)=='T')
        {
          pval=pulseIn(pnum,LOW,digitTime(a.substring(8)));
        }
        else
        {
          pval=pulseIn(pnum,LOW);
        }
        clnt.sendBinary("P:"+pin_name[indx]+":"+String(pval));
      }
      else
      {
        clnt.sendBinary("P:INVALID PIN COMMAND");
      }
    }
  }
  else
  {
    clnt.sendBinary("P:INVALID PIN COMMAND");
  }
}

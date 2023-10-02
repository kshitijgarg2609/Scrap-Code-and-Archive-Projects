#include "replyinterface.h"
#include <ArduinoWebsockets.h>

String model="ESP8266-01";
String service="SERVICE :- UART";

boolean wcon=false;
boolean wscon=false;
boolean dcon=false;
boolean rcon=false;

boolean ping_flg=true;
boolean ping_chk=false;

using namespace websockets;
WebsocketsClient clnt;

void onMessageCallback(WebsocketsMessage message)
{
  String msg;
   if(message.isBinary()==true)
   {
       msg=message.data();
    if(msg.charAt(0)=='X')
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

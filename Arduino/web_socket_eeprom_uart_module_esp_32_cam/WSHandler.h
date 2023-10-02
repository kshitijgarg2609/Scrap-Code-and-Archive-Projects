#include <ArduinoWebsockets.h>
#include "PacketFragmentModule.h"
#include "camera_frame_data.h"

String model="ESP32 CAM";
String service="SERVICE :- UART, CAM";

boolean wcon=false;
boolean wscon=false;
boolean dcon=false;
boolean rcon=false;

boolean ping_flg=true;
boolean ping_chk=false;

boolean frame_send=false;

using namespace websockets;
WebsocketsClient clnt;

void onMessageCallback(WebsocketsMessage message)
{
  String msg;
   if(message.isBinary()==true)
   {
       msg=message.data();
       if(msg.charAt(0)=='F')
       {
        if(msg.equals("F:START LIVE"))
        {
          frame_send=true;
          return;
        }
        else if(msg.equals("F:STOP LIVE"))
        {
          frame_send=false;
          return;
        }
        if(getFrame()==1)
      {
        
        unsigned int flen=frame->len;
        initPacketDivider(flen);
        for(unsigned int i=0;i<flen;i++)
        {
          if(writePacket(frame->buf[i])==1)
          {
            clnt.sendBinary((char*)pkt,pkt_len);
          }
        }
      }
      else
      {
        clnt.sendBinary("F:FRAME ERROR");
      }
       }
    if(msg.charAt(0)=='X')
    {
      if(!cnfg)
      {
        msg=msg.substring(2);
      }
      Serial.println(msg);
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
        Serial.println(msg);
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

void startProcess()
{
  initCam();
}

void sendLiveFrames()
{
  if(frame_send)
  {
    if(getFrame()==1)
      {
        
        unsigned int flen=frame->len;
        initPacketDivider(flen);
        for(unsigned int i=0;i<flen;i++)
        {
          if(writePacket(frame->buf[i])==1)
          {
            clnt.sendBinary((char*)pkt,pkt_len);
          }
        }
      }
  }
}

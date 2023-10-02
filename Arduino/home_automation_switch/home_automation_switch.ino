#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

int opto_isolator_pin=0;
int touch_sensor_pin=2;

boolean tflg=false;
boolean oflg;

void setup()
{
  pinMode(opto_isolator_pin,OUTPUT);
  pinMode(touch_sensor_pin,INPUT_PULLUP);
  digitalWrite(touch_sensor_pin,LOW);
  toggle(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  server.on("/",[]()
  {
    server.send(200,"text/html",getHtmlPage());
    if(server.hasArg("switch"))
    {
      String a=server.arg("switch");
      if(a.equals("on"))
      {
        toggle(true);
      }
      else if(a.equals("off"))
      {
        toggle(false);
      }
    }
  });
  server.begin();
}

String getHtmlPage()
{
  String a="\
  <!DOCTYPE html>\
  <html>\
  <body>\
  <form action='/' method='post'>\
  <button name = 'switch' type='submit' value = 'on'>SWITCH ON</button>\
  </form>\
  <br>\
  <br>\
  <form action='/' method='post'>\
  <button name = 'switch' type='submit' value = 'off'>SWITCH OFF</button>\
  </form>\
  </body>\
  </html>";
  return a;
}

void loop()
{
  server.handleClient();
  processFunction();
}

void processFunction()
{
  boolean cflg=(digitalRead(touch_sensor_pin)==HIGH);
  if(tflg==cflg)
  {
    return;
  }
  tflg=cflg;
  if(!tflg)
  {
   toggleSystem();
   delay(1);
  }
}

void toggleSystem()
{
  if(!oflg)
  {
    toggle(true);
  }
  else
  {
    toggle(false);
  }
}

void toggle(boolean a)
{
  analogWrite(opto_isolator_pin,(a?400:0));
  oflg=a;
}

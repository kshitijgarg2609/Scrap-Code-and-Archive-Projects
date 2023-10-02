#include <WiFi.h>
#include "camera_frame_data.h"

WiFiServer server(80);
WiFiClient client;

void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("K","123456789");
  initCam();
  server.begin();
}

void loop()
{
  if(!client || !client.connected())
  {
    client=server.available();
  }
  else
  {
    if(getFrame())
    {
      client.print("--frame\n");
      client.print("Content-Type: image/jpeg\n\n");
      client.flush();
      client.write(frame->buf, frame->len);
      client.flush();
      client.print("\n");
      esp_camera_fb_return(frame);
    }
  }
}

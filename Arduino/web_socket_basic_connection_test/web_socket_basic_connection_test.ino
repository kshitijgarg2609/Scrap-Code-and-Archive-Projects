#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

uint8_t bdata[10240];
unsigned int len=0;

const char* ssid = "sabka baap"; //Enter SSID
const char* password = "sabkabaap2609"; //Enter Password
const char* websockets_server = "ws://192.168.43.34:8080/WSEchoTest/EchoTest"; //server adress and port
const char* key = "IR1234567";

static boolean con=false;


using namespace websockets;

void onMessageCallback(WebsocketsMessage msg)
{
  if(msg.isBinary()==true)
  {
    Serial.println("Text Data");
  }
  else if(msg.isText()==true)
  {
    Serial.println("Binary Data");
  }
    Serial.print("Got Message: ");
    Serial.println(msg.data());
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if(event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Server Connected !!!");
        con=true;
    }
    else if(event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Server Disconnected !!!");
        con=false;
    }
    else if(event == WebsocketsEvent::GotPing)
    {
        Serial.println("Got a Ping!");
    }
    else if(event == WebsocketsEvent::GotPong)
    {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;

void initBin(unsigned int xyz)
{
  len=xyz;
  for(int i=0;i<len;i++)
  {
    bdata[i]=(uint8_t)('K');
  }
}

void setup()
{
    initBin(8192);
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    // Connect to server
    //client.connect(websockets_server);

    // Send a message
    //client.send("Hi Server!");
    // Send a ping
    //client.ping();
}

void loop()
{
  if(con)
  {
    delay(2000);
    client.poll();
    client.send(key);
    client.sendBinary((char*)bdata,len);
  }
  else
  {
    delay(500);
    client.connect(websockets_server);
    Serial.println("Connecting ...");
  }
}

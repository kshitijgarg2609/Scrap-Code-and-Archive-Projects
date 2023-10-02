#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

#define FIREBASE_HOST "demonstration-49368-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "bzo9ZWF22xbjGUyPKkZ9p6HS6LKJLj5owsR4hydX"
#define WIFI_SSID "xyz"
#define WIFI_PASSWORD "123456789"

FirebaseData firebaseData;

FirebaseJson json;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  Firebase.setString(firebaseData,"/",String(millis()));
  delay(3000);
}

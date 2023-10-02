#include <SoftwareSerial.h>
#include <Gpsneo.h>
//Gpsneo gps;
Gpsneo gps(D6,D7,9600);

char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];


void  setup()
{
    Serial.begin(115200);
}
void loop()
{
    //Just simple do getDataGPRMC, and the method solve everything.
    gps.getDataGPRMC(latitud,
                    latitudHemisphere,
                    longitud,
                    longitudMeridiano);

   Serial.println(latitud);
   Serial.println(latitudHemisphere);
   Serial.println(longitud);
   Serial.println(longitudMeridiano);
   
}

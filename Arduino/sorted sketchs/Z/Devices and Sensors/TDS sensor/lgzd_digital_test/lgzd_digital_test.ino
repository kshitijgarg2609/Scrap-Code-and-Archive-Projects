//int ledPin = 13;                // Connect an LED on pin 13, or use the onboard one
int sensor_in = 8;                 // Connect turbidity sensor to Digital Pin 2

void setup(){
  //pinMode(ledPin, OUTPUT);      // Set ledPin to output mode
  Serial.begin(9600);
  pinMode(sensor_in, INPUT);       //Set the turbidity sensor pin to input mode
}

void loop(){
  if(digitalRead(sensor_in)==LOW){       //read sensor signal
    Serial.println("Sensor is high");
  }
  else{
    Serial.println("Sensor is high");    // if sensor is HIGH, then turn off the led
  }
  delay(500);
}

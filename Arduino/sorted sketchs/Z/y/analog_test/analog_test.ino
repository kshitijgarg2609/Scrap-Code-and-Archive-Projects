 // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read

void setup() {
  Serial.begin(9600); 
 pinMode(10,INPUT);//  setup serial
}

void loop() {
  val = analogRead(10);  // read the input pin
  Serial.println(val);
  delay(1000);// debug value
}

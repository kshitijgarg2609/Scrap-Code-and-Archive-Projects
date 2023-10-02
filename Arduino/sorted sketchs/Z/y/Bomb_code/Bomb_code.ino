int i;
int arr[5];     // the number of the LED pin
int pin[5];
// variables will change:         // variable for reading the pushbutton status

void setup() {
  for(i=0;i<5;i++)
  {
   pin[i]=i+2;
   arr[i]=0;
   pinMode(pin[i],INPUT); 
  }
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin (9600);
}

void loop()
{
  for(i=0;i<5;i++)
  {
    arr[i]=digitalRead(pin[i]);
  }
  if(arr[2]==0)
  {
       digitalWrite(13,HIGH);
       delay(350);
       digitalWrite(13,LOW);
  }
  if(arr[1]==0||arr[3]==0)
  {
    digitalWrite(12,HIGH);
       delay(350);
       digitalWrite(12,LOW);
  }
Serial.print(arr[0]);
Serial.print(arr[1]);
Serial.print(arr[2]);
Serial.print(arr[3]);
Serial.print(arr[4]);
Serial.println();
delay(500);
}

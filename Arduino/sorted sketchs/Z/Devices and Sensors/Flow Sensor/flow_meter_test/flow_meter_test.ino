#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter Meter = FlowMeter(2);
//int x=0;
// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;
int snap;
//int ;
float rt;
//boolean bk=true;
// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void MeterISR() {
    // let our flow meter count the pulses
    //Serial.println("check");
    //cm=millis();
    
    Meter.count();
    
    //cm=millis()-cm;
    //Serial.println("check :-   "+cm);
    //ft+=cm;
    if((millis()-snap)>=1000)
    {
      snap=millis();
      Meter.tick(1000);
      rt=Meter.getCurrentFlowrate();
      Meter.reset();
      //Serial.println("check :- "+String(rt));
      //ft=0;
    }
}

void setup() {
    // prepare serial communication
    Serial.begin(9600);

    // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
    // do this setup step for every ISR you have defined, depending on how many interrupts you use
    attachInterrupt(INT0, MeterISR, RISING);

    // sometimes initializing the gear generates some pulses that we should ignore
    Meter.reset();
    snap=millis();
}

void loop() {
    // wait between output updates
    //x=millis();
    delay(1000);
    //Serial.println("check");
    // process the (possibly) counted ticks
    //Meter.tick(1000);
//float ff=Meter.getCurrentFlowrate();
    // output some measurement result
    //Serial.println("Currently " + String(Meter.getCurrentFlowrate()) + " l/min, " + String(Meter.getTotalVolume())+ " l total.");
    Serial.println(rt);
    //x=millis()-x;
    //Serial.println("check :- "+String(x));
    //
    // any other code can go here
    //
}

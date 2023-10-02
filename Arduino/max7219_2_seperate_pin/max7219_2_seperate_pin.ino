//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);
LedControl lc2=LedControl(9,8,7,1);
/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
  lc2.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc2.setIntensity(0,15);
  /* and clear the display */
  lc2.clearDisplay(0);
}

void loop()
{
  for(int i=0;i<10;i++)
  {
    //lc.setRow(0, 0, pgm_read_byte_near(charTable + i));
    lc.setColumn(0, 1, pgm_read_byte_near(charTable + i));
    lc2.setColumn(0, 1, pgm_read_byte_near(charTable + i));
    delay(delaytime);
  }
}

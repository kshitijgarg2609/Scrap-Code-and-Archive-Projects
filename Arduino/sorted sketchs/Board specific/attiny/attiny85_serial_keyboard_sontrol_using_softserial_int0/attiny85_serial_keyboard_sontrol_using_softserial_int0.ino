#include <DigiKeyboard.h>
#include <SoftSerial_INT0.h>

#define P_RX 2                        // Reception PIN (SoftSerial)
#define P_TX 1                        // Transmition PIN (SoftSerial)

SoftSerial sp(P_RX, P_TX);           // Software serial port for control the Bluetooth module

void setup()
{
    sp.begin(9600); // Initialize the serial port
}

void loop()
{
    if(sp.available())
    {
        sp.write(sp.read(),1);
    }
}

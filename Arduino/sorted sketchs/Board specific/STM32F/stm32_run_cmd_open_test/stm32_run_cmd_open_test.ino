#include <USBComposite.h>
//#include <Keyboard.h>

USBHID HID;
HIDKeyboard BootKeyboard(HID, 0);

void setup() 
{
    HID.begin(HID_BOOT_KEYBOARD);
    BootKeyboard.begin(); // needed just in case you need LED support
}

void loop() 
{
  BootKeyboard.press(KEY_LEFT_GUI);
  BootKeyboard.press('R');
  //BootKeyboard.getKeyCode('A',&KEY_LEFT_CTRL);
  BootKeyboard.releaseAll();
  delay(4000);
}

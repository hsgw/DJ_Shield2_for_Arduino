#ifndef Re_h
#define Re_h

#include "Arduino.h"

//PORTB
//D10 and D11
#define re_Input_Mask B110011
#define re_Pin_Mask B001100

class Re{
  public:
    Re();
    void update();
    boolean changed();
    int value();
  private:
    volatile boolean re_Moved;
    volatile int re_Dir;
    volatile byte index;
};

#endif

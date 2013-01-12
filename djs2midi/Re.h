#ifndef Re_h
#define Re_h

#include "Arduino.h"

const int dir[] = { 0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0 };

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
    boolean re_Moved;
    int re_Dir;
    byte index;
    unsigned long last_Time;
};

#endif

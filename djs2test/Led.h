#ifndef Led_h
#define Led_h

#include "Arduino.h"

#define LED_A 12
#define LED_B 7

class Led{
  public:
    Led();
    void toggle(int pin);
    void control(int pin, boolean state);
  private:
    boolean state_A;
    boolean state_B;
};

#endif

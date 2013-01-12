#ifndef Sw_h
#define Sw_h

#include "Arduino.h"

//PORTD
#define pin_control_165_Mask B01100000
#define CLK_Pin_HIGH_Mask    B00100000
#define CLK_Pin_LOW_Mask     B11011111
#define SH_Pin_HIGH_Mask     B01000000
#define SH_Pin_LOW_Mask      B10111111
//PORTB
#define pin_input_165_Mask   B11111100
#define pin_Out1_Mask        B00000001
#define pin_Out2_Mask        B00000010

#define debounce_Count       3

class Sw{
  public:
    Sw();
    void update();
    boolean changed(int);
    boolean value(int);
  private:
    void bounce();
    boolean last_Sw_State[2][8];
    boolean current_Sw_State[2][8];
    boolean changed_Sw_State[2][8];
    boolean sw_State[2][8];
    int sw_Counter[2][8];
};

#endif

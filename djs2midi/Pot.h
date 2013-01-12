#ifndef Pot_h
#define Pot_h

#include "Arduino.h"

#define pin_control_4051 B00011100
#define pin_control_4051_Mask B11100011
#define analog_pin_4051 5

const byte value_Control_4051[8] = {B00000,B10000,B01000,B11000,B00100,B10100,B01100,B11100};

class Pot{
  public:
    Pot(boolean _pot_Direction = true);
    void update();
    boolean changed(int);
    int value(int);
    int raw_Value(int);
  private:
    boolean pot_Direction;
    int center_Max;
    int center_Min;
    int current_Value_Raw[13];
    int current_Value[13];
    int last_Value[13];
    int temp_Value;
    boolean value_Changed[13];
    void read_4051();
    void read_Analog_Pin();
    int parse_Value(int);
};

#endif

#include "Arduino.h"
#include "Pot.h"

Pot::Pot(boolean _pot_Direction)
{
  pot_Direction = _pot_Direction;
  DDRD = DDRD | pin_control_4051;
}

void Pot::update(){
  int temp_Value[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
  for(int count = 0;count<4;count++){
    read_Analog_Pin();
    read_4051();
    for(int i=0;i<13;i++){
      temp_Value[i] += parse_Value(current_Value_Raw[i]);
    }
  }
  
  for(int i = 0;i<13;i++){
    temp_Value[i] = temp_Value[i] >> 2;
    if(temp_Value[i] == 127){
      current_Value[i] = 127;
    }else{
      current_Value[i] = (last_Value[i] + temp_Value[i]) >> 1;
    }
  }
  
  for(int i=0;i<13;i++){
    if(current_Value[i] != last_Value[i]){
      value_Changed[i] = true;
      last_Value[i] = current_Value[i];
    }else{
      value_Changed[i] = false;
    }
  }
}

boolean Pot::changed(int no){
  boolean temp_Changed = value_Changed[no];
  value_Changed[no] = false;
  return temp_Changed;
}

int Pot::value(int no){
  return current_Value[no];
}

int Pot::raw_Value(int no){
  return current_Value_Raw[no];
}

void Pot::read_4051(){
  for(int i=0;i<8;i++){
    PORTD = PORTD & pin_control_4051_Mask;
    PORTD = PORTD | value_Control_4051[i];
    delayMicroseconds(2);
    current_Value_Raw[i+5] = analogRead(analog_pin_4051);
  }
}

void Pot::read_Analog_Pin(){
  for(int i=0;i<5;i++){
    current_Value_Raw[i] = analogRead(i);
  }
}

int Pot::parse_Value(int temp_Value){
  temp_Value = temp_Value >> 3;
  if(pot_Direction){
    return 127 - temp_Value;
  }else{
    return temp_Value;
  }
}

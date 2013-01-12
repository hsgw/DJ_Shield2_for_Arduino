#include "Sw.h"

Sw::Sw(){
  DDRD = DDRD | pin_control_165_Mask;
  DDRB = DDRB & pin_input_165_Mask;
  
  PORTD = PORTD & CLK_Pin_LOW_Mask;
  PORTD = PORTD | SH_Pin_HIGH_Mask;
  
  for(int i=0;i<2;i++){
    for(int j=0;j<8;j++){
      current_Sw_State[i][j] = false;
      last_Sw_State[i][j] = false;
      changed_Sw_State[i][j] = false;
      sw_State[i][j] = false;
      sw_Counter[i][j] = 0;
    }
  }
}

void Sw::update(){
  byte temp;
  
  PORTD = PORTD & SH_Pin_LOW_Mask;
  PORTD = PORTD | SH_Pin_HIGH_Mask;
  
  for(int i=0;i<8;i++){
    last_Sw_State[0][i] = current_Sw_State[0][i];
    last_Sw_State[1][i] = current_Sw_State[1][i];
    
    temp = ~(PINB & 0b00000011);
    
    if((temp & pin_Out1_Mask) == 0b01){
      current_Sw_State[0][i] = true;
    }else{
      current_Sw_State[0][i] = false;
    }
    
    if((temp & pin_Out2_Mask) == 0b10){
      current_Sw_State[1][i] = true;
    }else{
      current_Sw_State[1][i] = false;
    }
    
    PORTD = PORTD & CLK_Pin_LOW_Mask;
    PORTD = PORTD | CLK_Pin_HIGH_Mask;
  }
  bounce();
}

boolean Sw::changed(int no){
  int index,bit_Pos;
  boolean temp_Changed;
  
  if(no<8){
      index = 0;
      bit_Pos = no;
  }else if(no<12){
      index = 1;
      bit_Pos = no - 4;
  }else if(no<16){
      index = 1;
      bit_Pos = no - 12;
  }
  
  temp_Changed = changed_Sw_State[index][bit_Pos];
  changed_Sw_State[index][bit_Pos] = false;
  return temp_Changed;
}

boolean Sw::value(int no){
  int index,bit_Pos;
  
  if(no<8){
      index = 0;
      bit_Pos = no;
  }else if(no<12){
      index = 1;
      bit_Pos = no - 4;
  }else if(no<16){
      index = 1;
      bit_Pos = no - 12;
  }
  return sw_State[index][bit_Pos];
}

void Sw::bounce(){
  for(int i=0;i<2;i++){
    for(int j=0;j<8;j++){
      if(current_Sw_State[i][j] != last_Sw_State[i][j]){
        sw_Counter[i][j] = debounce_Count;
      }else{
        if(sw_Counter > 0){
          sw_Counter[i][j]--;
          if(sw_Counter[i][j] == 0){
            changed_Sw_State[i][j] = true;
            sw_State[i][j] = current_Sw_State[i][j];
          }
        }
      }
    }
  }
}

#include "Arduino.h"
#include "Re.h"


Re::Re(){
  re_Moved = false;
  re_Dir = 1;
  index = 0;
  DDRB = DDRB & re_Input_Mask;
}

void Re::update(){
    index = ((index << 2) + ((PINB & re_Pin_Mask) >> 2)) & 15;
    switch(index){
      case B0111:
        re_Dir++;
        re_Moved = true;
//      Serial.println("+");
        break;
      case B1101:
        re_Dir--;
        re_Moved = true;
 //     Serial.println("-");
        break;
      default:break;
     }
}

boolean Re::changed(){
  boolean temp_Moved = re_Moved;
  re_Moved = false;
  return temp_Moved;
}

int Re::value(){
  int temp_Dir = re_Dir;
  re_Dir = 0;
  return temp_Dir;
}

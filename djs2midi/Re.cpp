#include "Arduino.h"
#include "Re.h"

Re::Re(){
  re_Moved = false;
  re_Dir = 1;
  index = 0;
  last_Time = 0;
  DDRB = DDRB & re_Input_Mask;
}

void Re::update(){
  int n = 0;
  unsigned long time = millis();
  if(time - last_Time > 1){
    index = ((index << 2) + ((PINB & re_Pin_Mask) >> 2)) & 15;
    switch(index){
      case 0b0111:
        re_Dir++;
        re_Moved = true;
        last_Time = time;
//      Serial.println("+");
        break;
      case 0b1011:
        re_Dir--;
        re_Moved = true;
        last_Time = time;
 //     Serial.println("-");
        break;
      default:break;
     }
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

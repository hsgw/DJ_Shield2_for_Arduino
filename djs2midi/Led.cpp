#include "Arduino.h"
#include "Led.h"

Led::Led(){
  pinMode(LED_A,OUTPUT);
  pinMode(LED_B,OUTPUT);
  state_A = false;
  state_B = false;
}

void Led::toggle(int pin){
  switch(pin){
    case 1:
      state_A = ~state_A;
      digitalWrite(LED_A,state_A);
      break;
    case 2:
      state_B = ~state_B;
      digitalWrite(LED_B,state_B);
      break;
    default: break;
  }
}

void Led::control(int pin, boolean state){
  switch(pin){
    case 1:
      state_A = state;
      digitalWrite(LED_A,state_A);
      break;
    case 2:
      state_B = state;
      digitalWrite(LED_B,state_B);
      break;
    default: break;
  }
}

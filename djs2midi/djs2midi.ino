/*
 DJ Shield 2 for Arduino - MIDI sketch
 by dm9 records

  * Send MIDI Data on USB-Serial.(31250bps)
  * Moco for LUFA compatible
    http://web.mac.com/kuwatay/morecat_lab./MocoLUFA.html
  
  more infomation : http://www.dm9records.com
  
  This code and schmantics is in Creative Commons 3.0 BY-SA
  http://creativecommons.org/licenses/by-sa/3.0/
  
  ----VERSION------
  10/--/2011 v1.0
  01/13/2012 v2.0 improve response
  12/07/2014 v2.1 update MIDI library(please use MIDI Library v4.2)
  
*/

// select midi baudrate
#define MIDI_BAUDRATE 31250
//#define MIDI_BAUDRATE 57600

#include <MIDI.h>

#include <MsTimer2.h>

#include "Led.h"
#include "Pot.h"
#include "Sw.h"
#include "Re.h"

const byte midiCC[13] = {16,17,18,19,20,21,22,23,24,25,26,27,28};
const byte midiNote[12] = {60,61,62,63,64,65,66,67,68,69,70,71};
const byte midiRE[2] = {10,11};

Led LED;
Pot POT = Pot();
Sw SW = Sw();
Re RE = Re();

struct MySetting : public midi::DefaultSettings {
  static const long BaudRate = MIDI_BAUDRATE;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial,Serial,MIDI,MySetting);
//midi::MidiInterface<HardwareSerial, MySetting> MIDI((HardwareSerial&)Serial);

void setup(){
  LED.control(1,HIGH);
  LED.control(2,HIGH);
  delay(500);
  LED.control(1,LOW);
  LED.control(2,LOW);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  POT.init();
  MsTimer2::set(3,re_Update);
  MsTimer2::start();
}

void loop(){
  int reValue = 0;
  MIDI.read();
  POT.update();
  SW.update();
  
  for(int i=0;i<13;i++){
    if(POT.changed(i)){
      MIDI.sendControlChange(midiCC[i],POT.value(i),1);
    }
  }
  for(int i=0;i<12;i++){
    if(SW.changed(i)){
      if(SW.value(i)==1){
        MIDI.sendNoteOn(midiNote[i],127,1);
      }else{
        MIDI.sendNoteOff(midiNote[i],127,1);
      }
    }
  }
  if(RE.changed()){
    reValue = RE.value();
    if(reValue<0){
      for(int i=0;i>reValue;i--){
        MIDI.sendNoteOn(midiRE[0],127,1);
        MIDI.sendNoteOff(midiRE[0],127,1);
      }
    }else if(reValue > 0){
      for(int i=0;i<reValue;i++){
        MIDI.sendNoteOn(midiRE[1],127,1);
        MIDI.sendNoteOff(midiRE[1],127,1);
      }
    }
  }
}

void re_Update(){
  RE.update();
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if(pitch == 0){
    LED.control(1,HIGH);
    if(velocity == 0){
      LED.control(1,LOW);
    }
  }else if(pitch == 1){
    LED.control(2,HIGH);
    if(velocity == 0){
      LED.control(2,LOW);
    }
  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  if(pitch == 0){
    LED.control(1,LOW);
  }else if(pitch == 1){
    LED.control(2,LOW);
  }
}

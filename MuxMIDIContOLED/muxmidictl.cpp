/******************************************************
 Inspired from:
 MIDI CONTROLLER
 by Notes and Volts
 www.notesandvolts.com
 Version 1.0 **Arduino UNO ONLY **

 Adapted by Arda EDEN for TEENSY 3.2 (2016)
 ardaeden@gmail.com
******************************************************/

#include "muxmidictl.h"
#include <Arduino.h>

Mux::Mux(int teensyInputPin_) {
  teensyInputPin = teensyInputPin_;
}


Pot::Pot(Mux mux_, char potName_[5] ,int potMuxPin_, int potControl_, int potChannel_){
  potControl = potControl_;
  potChannel = potChannel_;
  strcpy(_potName, potName_);
  _potTeensyPin = mux_.teensyInputPin;
  _potMuxPin = potMuxPin_;
  _potValue = analogRead(_potMuxPin);
  _potOldValue = _potValue;
}

void Pot::muxPotSelect() {
  int tmp = _potMuxPin;
  tmp = tmp << 2;
  PORTD &= 0b11100011;
  PORTD |= tmp;
}

int Pot::getPotValue() {
  muxPotSelect();
  _potValue = analogRead(_potTeensyPin);
  
  if (abs(_potOldValue - _potValue) > 10) {
    _potOldValue = _potValue;
    return _potValue / 8;
  }
  return 255;
}

char *Pot::getPotName() {
  return _potName;
}



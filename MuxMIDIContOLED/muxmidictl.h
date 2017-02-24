/******************************************************
 Inspired from:
 MIDI CONTROLLER
 by Notes and Volts
 www.notesandvolts.com
 Version 1.0 **Arduino UNO ONLY **

 Adapted by Arda EDEN for TEENSY 3.2 (2016)
 ardaeden@gmail.com
******************************************************/

#ifndef muxmidictl_h
#define muxmidictl_h

class Mux {
  public:
    Mux(int teensyInputPin_);
    int teensyInputPin;  
};

class Pot {
  public:
    Pot(Mux mux, char potName[5], int potMuxPin, int potControl, int potChannel);
    int getPotValue();
    void muxPotSelect();
    char *getPotName();
    int potControl;
    int potChannel;
 
  private:
    int _potTeensyPin;
    int _potMuxPin;
    int _potValue;
    int _potOldValue;
    char _potName[5];
};
#endif

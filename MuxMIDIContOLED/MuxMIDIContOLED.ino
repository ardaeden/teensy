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
#include <MIDI.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//MIDI Definitions
#define NUM_POTS 4

//OLED Definitions
#define XPOS 0
#define YPOS 1
#define OLED_RESET 4

Mux M1(A0);
Mux M2(A1);

Pot P1(M1, "Pot1", 0, 20, 1);
Pot P2(M1, "Pot2", 1, 21, 1);
Pot P3(M2, "Pot3", 0, 22, 1);
Pot P4(M2, "Pot4", 1, 23, 2);

Pot *Pots[] {&P1, &P2, &P3, &P4};

Adafruit_SSD1306 display(OLED_RESET);




void setup() {
  initTeensy();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
}

void loop() {

  updateMIDI();
}

void initTeensy() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void updateMIDI() {
   for (int i = 0; i < NUM_POTS; i++) {
    int controlMsg = Pots[i]->getPotValue();
    if (controlMsg != 255) {
      display.setCursor(0,0);
      display.println(Pots[i]->getPotName());
      display.println(controlMsg);
      display.display();
      display.clearDisplay();
      usbMIDI.sendControlChange(Pots[i]->potControl, controlMsg, Pots[i]->potChannel);  
    }
  }
}


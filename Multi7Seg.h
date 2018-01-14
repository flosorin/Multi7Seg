#ifndef MULTI_7_SEG_H
#define MULTI_7_SEG_H

#include "Arduino.h"

/* Common cathode or anode mode */
typedef enum {COMMON_CATHODE, COMMON_ANODE} segMode;

/* 7 segment converted numbers */
const byte digit[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

/* Store a value with the number of digits used to display it */
typedef struct {
  int value;
  int digits;
} displayerValue;

class Multi7Seg {

public:
    Multi7Seg(int nbDigitsInit, int *digitPinsInit, int clockPinInit, int latchPinInit, 
      int dataPinInit, segMode modeInit = COMMON_CATHODE); // Constructor: define and initialize pins
    void updateDisplay(displayerValue *rawValues, int nbValues); // Update the displayer with given values (must be called in loop)
  
private :
    int nbDigits; // Number of 7 segment digits in the displayer
    int *digitPins;  // Common anode/cathode pins
    int *digitBuffer; // Buffer to store the state of the digits to latch
    int clockPin;    // 74HC595 pin 11 
    int latchPin;    // 74HC595 pin 12
    int dataPin;     // 74HC595 pin 14
    segMode mode;
    void initPins();
    void convertValue(displayerValue rawValue, int buffIndex); // Convert a raw value into the given number of digits and store it at the specified index
};

#endif // MULTI_7_SEG_H

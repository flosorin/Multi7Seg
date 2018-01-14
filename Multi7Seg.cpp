#include "Multi7Seg.h"

/* Constructor: define and initialize pins */
Multi7Seg::Multi7Seg(int nbDigitsInit, int *digitPinsInit, int clockPinInit, int latchPinInit, int dataPinInit, segMode modeInit) :
nbDigits(nbDigitsInit), digitPins(digitPinsInit), clockPin(clockPinInit), latchPin(latchPinInit), dataPin(dataPinInit), mode(modeInit) {

  digitBuffer = malloc(nbDigits * sizeof(int));
	initPins();
}

void Multi7Seg::initPins() {
  
  for(int i = 0; i < nbDigits; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
}

/* Update the displayer with given values (must be called in loop) */
void Multi7Seg::updateDisplay(displayerValue *rawValues, int nbValues) {
  
  static int digitScan = 0;
  int digitBufferIndex = nbDigits; // Store the current free position in the buffer

  /* Dispatch the values into digits in the buffer */
  for (int i = 0; i < nbValues; i++) {
    if (digitBufferIndex >= 1) {
      convertValue(rawValues[i], digitBufferIndex);
      digitBufferIndex -= rawValues[i].digits;
    }
  }
  
  for(int i = 0; i < nbDigits; i++) {
	if (mode == COMMON_CATHODE) {
	  digitalWrite(digitPins[i], HIGH);
    } else {
      digitalWrite(digitPins[i], LOW);
    }
  }
  
  digitalWrite(latchPin, LOW);
  if (mode == COMMON_CATHODE) {
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
  } else {
    shiftOut(dataPin, clockPin, MSBFIRST, B11111111);
  }
  digitalWrite(latchPin, HIGH);

  delayMicroseconds(100);

  if (mode == COMMON_CATHODE) {
     digitalWrite(digitPins[digitScan], LOW);
  } else {
     digitalWrite(digitPins[digitScan], HIGH);
  }
  
  digitalWrite(latchPin, LOW);
  if (mode == COMMON_CATHODE) {
     shiftOut(dataPin, clockPin, MSBFIRST, digit[digitBuffer[digitScan]]);
  } else {
     shiftOut(dataPin, clockPin, MSBFIRST, ~digit[digitBuffer[digitScan]]);
  }
  digitalWrite(latchPin, HIGH);
  
  digitScan++;
  if(digitScan > nbDigits) {
    digitScan=0; 
  }
}

/* Convert a raw value into the given number of digits and store it at the specified index */
void Multi7Seg::convertValue(displayerValue rawValue, int buffIndex) {

  int value = rawValue.value, digits = rawValue.digits;
  
  digitBuffer[buffIndex - 1] = value / pow(10, digits - 1);
  
  if ((digits > 1) && ((buffIndex - digits) >= 0)) {
    for (int i = digits - 2; i >= 0; i--) {
      digitBuffer[buffIndex + i - digits] = (value % (int)pow(10, i + 1)) / pow(10, i);
    }
  }
}

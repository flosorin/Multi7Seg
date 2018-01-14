/************************************************************************
* This example demonstrate the feature which allows controlling 
* the digits separately, by running two 2-digits counters.
*
* Using Simon Monk's Timer library
* http://www.doctormonk.com/2012/01/arduino-timer-library.html
*
* Multi7Seg library by Florian Sorin (2018) 
* https://github.com/captainBarbu/Multi7Seg.git
* 
* ***********************************************************************/

#include <Event.h>
#include <Timer.h>
#include <Multi7Seg.h>

#define NB_7_SEG 4
#define PIN_DIGIT0 3
#define PIN_DIGIT1 4
#define PIN_DIGIT2 5
#define PIN_DIGIT3 6
#define PIN_CLK A4
#define PIN_LATCH A3
#define PIN_DATA A2

int displayerPins[5] = {PIN_DIGIT0, PIN_DIGIT1, PIN_DIGIT2, PIN_DIGIT3};

Timer countingTimer;
Multi7Seg displayer = Multi7Seg(NB_7_SEG, displayerPins, PIN_CLK, PIN_LATCH, PIN_DATA, COMMON_CATHODE);
displayerValue values[2] = {{0, 2}, {5, 2}}; // 2 values of 2 digits, different initial value

void setup() {
   
  Serial.begin(9600);
  countingTimer.every(1000, incrementFourDigitsCounter);              
}

void loop() {
   
  displayer.updateDisplay(values, 2);
  countingTimer.update();
  delay(2);
}

void incrementFourDigitsCounter() {
  
  values[0].value = incrementValue(values[0].value);
  values[1].value = incrementValue(values[1].value);
}

int incrementValue(int value) {

  value ++;
  
  if (value >= 100) {
    return 0;
  }

  return value;
}


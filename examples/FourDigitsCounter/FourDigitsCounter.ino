/************************************************************************
* This example uses four 7 segment displays to run a 4-digits counter.
*
* Using Simon Monk's Timer library
* http://www.doctormonk.com/2012/01/arduino-timer-library.html
*
* Multi7Seg library by Florian Sorin (2018) 
* https://github.com/flosorin/Multi7Seg.git
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

int displayerPins[4] = {PIN_DIGIT0, PIN_DIGIT1, PIN_DIGIT2, PIN_DIGIT3};

Timer countingTimer;
Multi7Seg displayer = Multi7Seg(NB_7_SEG, displayerPins, PIN_CLK, PIN_LATCH, PIN_DATA, COMMON_CATHODE);
displayerValue values[1] = {{0, 4}}; // Value 0 with a 4 digits representation

void setup() {
   
  Serial.begin(9600);
  countingTimer.every(1000, incrementCounter); // Increment counter every second               
}

void loop() {
   
  displayer.updateDisplay(values, 1); // Only one value used here
  countingTimer.update();
}

void incrementCounter() {
  
  values[0].value ++;

  if (values[0].value >= 10000) {
    values[0].value = 0;
  }
}

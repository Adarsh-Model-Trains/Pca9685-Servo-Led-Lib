/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "Pca9685Board.h"
#define NO_OF_SERVO_BOARDS 2
#define NO_OF_LIGHT_BOARDS 0

int MAX_PINS = 0;

Pca9685Board pca9685Board;

void setup() {
  Serial.begin(9600);
  pca9685Board.initPca9685Boards(NO_OF_SERVO_BOARDS, NO_OF_LIGHT_BOARDS);
  MAX_PINS = (NO_OF_SERVO_BOARDS * 16);
  for (int i = 1; i <= MAX_PINS; i++) {
    pca9685Board.setSwitchRange(i, 1200, 1800);
  }
}

void loop() {

  for (int i = 1; i <= 32; i++) {
    int pinNo = i;
    pca9685Board.throwSwitch(pinNo);
  }
  pca9685Board.displayPinState();
  delay(1000);
  for (int i = 1; i <= 32; i++) {
    int pinNo = i;
    pca9685Board.closeSwitch(pinNo);
  }
  pca9685Board.displayPinState();
  delay(1000);
}

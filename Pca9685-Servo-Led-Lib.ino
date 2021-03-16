
#include "Pca9685Board.h"

#define NO_OF_SERVO_BOARDS 1
#define NO_OF_LIGHT_BOARDS 1


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

  int pinNo = 1;
  Serial.print("PIN NO ");
  Serial.println(pinNo);
  delay(1000);
  pca9685Board.throwSwitch(pinNo);
  pinNo = 32;
  pca9685Board.switchOn(pinNo);
  pca9685Board.displayPinState();
  delay(1000);
  pinNo = 1;
  pca9685Board.closeSwitch(pinNo);
  pinNo = 32;
  pca9685Board.switchOff(pinNo);
  pca9685Board.displayPinState();

}

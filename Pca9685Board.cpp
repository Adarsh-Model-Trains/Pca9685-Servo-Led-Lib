/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "Pca9685Board.h"

void Pca9685Board::initPca9685Boards(int totalTurnoutBoard, int totalLightBoard) {

  if (totalLightBoard > -1 && totalLightBoard < 65) {
    _totalLightBoard = totalLightBoard;
    Serial.print("Total Pca9685 boards for Light ");
    Serial.println(totalLightBoard);
  } else {
    Serial.println("invalid arguments supplied");
    return;
  }

  if (totalTurnoutBoard > -1 && totalTurnoutBoard < 65) {
    _totalTurnoutBoard = totalTurnoutBoard;
    Serial.print("Total Pca9685 boards for Servo ");
    Serial.println(_totalTurnoutBoard);
  } else {
    Serial.println("invalid arguments supplied");
    return;
  }

  if ((totalTurnoutBoard + totalLightBoard) > 0 && (totalTurnoutBoard + totalLightBoard) < 65) {
    _totalPca9685Boards = (totalTurnoutBoard + totalLightBoard) ;
    Serial.print("Total Pca9685 boards for Servo and Light");
    Serial.println(_totalPca9685Boards);
  } else {
    Serial.println("invalid arguments supplied");
    _totalPca9685Boards = 0;
  }
  _pca9685Boards = new Pca9685[_totalPca9685Boards];
  int i = 0;
  if (_totalPca9685Boards > 0 && _totalTurnoutBoard != 0) {
    for (i = 0; i <  _totalTurnoutBoard; i++) {
      _pca9685Boards[i].setBoardAddress(_boardAddress[i]);
      _pca9685Boards[i].setPwmFrequency(_pwmFrequencyTurnout);
      _pca9685Boards[i].initPca9685('T');
    }
  }
  if (_totalPca9685Boards > 0 && _totalLightBoard != 0) {
    for ( ; i < _totalPca9685Boards; i++) {
      _pca9685Boards[i].setBoardAddress(_boardAddress[i]);
      _pca9685Boards[i].setPwmFrequency(_pwmFrequencyLight);
      _pca9685Boards[i].initPca9685('L');
    }
  }
}

void Pca9685Board::setFrequencyTurnout(int pwmFrequencyTurnout) {
  if (pwmFrequencyTurnout > 39 && pwmFrequencyTurnout < 1001) {
    _pwmFrequencyTurnout = pwmFrequencyTurnout;
  } else {
    Serial.println("default frequency set for Turnout 50");
    _pwmFrequencyTurnout = 50;
  }
}

void Pca9685Board::setFrequencyLight(int pwmFrequencyLight) {
  if (pwmFrequencyLight > 39 && pwmFrequencyLight < 1001) {
    _pwmFrequencyLight = pwmFrequencyLight;
  } else {
    Serial.println("default frequency set for light 1000");
    _pwmFrequencyLight = 1000;
  }
}

Pca9685Board::BoardPin Pca9685Board::findBoardPin(int pinNo) {
  Pca9685Board::BoardPin boardSlot;
  pinNo = pinNo - 1;
  int board = (pinNo / 16);
  if (board <= _totalPca9685Boards && pinNo <= (_totalPca9685Boards * 16)) {
    int totalPins = (board * 16);
    int pin = (pinNo - totalPins);
    pin = (pin == -1) ? 0 : pin;
    boardSlot.processed = true;
    boardSlot.boardNo = board;
    boardSlot.boardPin = pin;
    return boardSlot;
  }
  boardSlot.processed = false;
  return boardSlot;
}

bool Pca9685Board::throwSwitch(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (_pca9685Boards[boardSlot.boardNo].getType() == 'T') {
    _pca9685Boards[boardSlot.boardNo].throwSwitchPca9685Pin(boardSlot.boardPin);
    return true;
  } else {
    Serial.println("throwSwitch() for Turnout boards");
    return false;
  }
}

bool Pca9685Board::closeSwitch(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (_pca9685Boards[boardSlot.boardNo].getType() == 'T') {
    _pca9685Boards[boardSlot.boardNo].closeSwitchPca9685Pin(boardSlot.boardPin);
    return true;
  } else {
    Serial.println("closeSwitch() for Turnout boards");
    return false;
  }
}

void Pca9685Board::restBoard(int boardNo) {
  _pca9685Boards[boardNo].resetPca9685Board();
}

void Pca9685Board::refreshBoard(int boardNo) {
  _pca9685Boards[boardNo].refreshPca9685Board();
}

void Pca9685Board::setSwitchRange(int pinNo, int openRange, int closeRange) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (_pca9685Boards[boardSlot.boardNo].getType() == 'T') {
    _pca9685Boards[boardSlot.boardNo].setSwitchOpenCloseRange(boardSlot.boardPin, openRange, closeRange);
  } else {
    Serial.println("setSwitchRange() for Turnout boards");
  }
}

bool Pca9685Board::switchOn(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (_pca9685Boards[boardSlot.boardNo].getType() == 'L') {
    _pca9685Boards[boardSlot.boardNo].switchOnPca9685Pin(boardSlot.boardPin);
    return true;
  } else {
    Serial.println("switchOn() for Light boards");
    return false;
  }
}

bool Pca9685Board::switchOff(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (_pca9685Boards[boardSlot.boardNo].getType() == 'L') {
    _pca9685Boards[boardSlot.boardNo].switchOffPca9685Pin(boardSlot.boardPin);
    return true;
  } else {
    Serial.println("switchOff() for Light boards");
    return false;
  }
}

void Pca9685Board::displayPinState() {
  Serial.print("Total Boards ");
  Serial.println(_totalPca9685Boards);
  for (int i = 0; i < _totalPca9685Boards; i++) {
    _pca9685Boards[i].displayPca9685();
    Serial.println(" - ");
  }
}

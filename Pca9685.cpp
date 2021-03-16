/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include <Arduino.h>
#include "Pca9685.h"


void Pca9685::initPca9685(char type) {
  _pwm = Adafruit_PWMServoDriver(_boardsAddress);
  _pwm.begin();
  _pwm.setPWMFreq(_pwmFrequency);
  _type = type;
  if (_type == 'L') {
    _pca9685PinStateList = new bool[_totalPins];
    _pwmFrequency = 1000;
    for (int i = 0; i < _totalPins; i++) {
      _pca9685PinStateList[i] = false;
    }
  } else if (_type == 'T') {
    _pca9685PinList = new Pca9685Pin[_totalPins];
    for (int i = 0; i < _totalPins; i++) {
      _pca9685PinList[i]._openState = 1000;
      _pca9685PinList[i]._closeState = 2000;
      _pca9685PinList[i]._isOpen = false;
    }
  }
}

void Pca9685::setPwmFrequency(int pwmFrequency) {
  this->_pwmFrequency = pwmFrequency;
}

bool Pca9685::setSwitchOpenCloseRange(int pinNo, int openRange, int closeRange) {
  if (_type == 'T') {
    _pca9685PinList[pinNo]._openState = openRange;
    _pca9685PinList[pinNo]._closeState = closeRange;
    return true;
  } else {
    return false;
  }
}

void Pca9685::setBoardAddress(int boardsAddress) {
  this->_boardsAddress = boardsAddress;
}

bool Pca9685::throwSwitchPca9685Pin(int pinNo) {
  if (_type == 'T') {
    _pca9685PinList[pinNo]._isOpen = true;
    Pca9685Pin pin = _pca9685PinList[pinNo];
    refreshPin(pinNo, pin);
    return true;
  } else {
    return false;
  }
}

bool Pca9685::closeSwitchPca9685Pin(int pinNo) {
  if (_type == 'T') {
    _pca9685PinList[pinNo]._isOpen = false;
    Pca9685Pin pin = _pca9685PinList[pinNo];
    refreshPin(pinNo, pin);
    return true;
  } else {
    return false;
  }
}

void Pca9685::resetPca9685Board() {
  if (_type == 'T') {
    for (int i = 0; i < _totalPins; i++) {
      _pca9685PinList[i]._isOpen = false;
    }
  } else  if (_type == 'L') {
    for (int i = 0; i < _totalPins; i++) {
      _pca9685PinStateList[i] = false;
    }
  }
  refreshPca9685Board();
}

void Pca9685::refreshPca9685Board() {
  if (_type == 'T') {
    for (int i = 0; i < _totalPins; i++) {
      Pca9685Pin pca9685Pin = _pca9685PinList[i];
      if (pca9685Pin._isOpen) {
        _pwm.writeMicroseconds(i, pca9685Pin._openState );
      } else {
        _pwm.writeMicroseconds(i, pca9685Pin._closeState );
      }
    }
  } else  if (_type == 'L')  {
    for (int i = 0; i < _totalPins; i++) {
      bool state = _pca9685PinStateList[i];
      if (state) {
        _pwm.setPWM(i, 4096, 0);
      } else {
        _pwm.setPWM(i, 0, 4096);
      }
    }
  }
}

void Pca9685::refreshPin(int pinNo, Pca9685Pin pca9685Pin) {
  if (_type == 'T') {
    if (pca9685Pin._isOpen) {
      _pwm.writeMicroseconds(pinNo, pca9685Pin._openState );
    } else {
      _pwm.writeMicroseconds(pinNo, pca9685Pin._closeState );
    }
  }
}

void Pca9685::refreshPin(int pinNo, bool state) {
  if (_type == 'L') {
    if (state) {
      _pwm.setPWM(pinNo, 4096, 0);
    } else {
      _pwm.setPWM(pinNo, 0, 4096);
    }
  }
}

bool Pca9685::switchOnPca9685Pin(int pinNo) {
  if (_type == 'L') {
    _pca9685PinStateList[pinNo] = true;
    refreshPin(pinNo, true);
    return true;
  } else {
    return false;
  }
}

bool Pca9685::switchOffPca9685Pin(int pinNo) {
  if (_type == 'L') {
    _pca9685PinStateList[pinNo] = false;
    refreshPin(pinNo, false);
    return true;
  } else {
    return false;
  }
}

char Pca9685::getType() {
  return _type;
}

void Pca9685::displayPca9685() {
  Serial.print("Board No ");
  Serial.print(_boardsAddress);
  Serial.print(" total pins ");
  Serial.println(this->_totalPins);
  if (_type == 'L') {
    for (int i = 0; i < _totalPins; i++) {
      bool state = _pca9685PinStateList[i];
      Serial.println();
      Serial.print(" Pin ");
      Serial.print(i);
      Serial.print(" PinState ");
      Serial.println(((state) ? "ON" : "OFF"));
    }
  } else if (_type == 'T') {
    for (int i = 0; i < this->_totalPins; i++) {
      Pca9685Pin pin = _pca9685PinList[i];
      Serial.println();
      Serial.print(" Pin ");
      Serial.print(i);
      Serial.print(" openState ");
      Serial.print(pin._openState);
      Serial.print(" closeState ");
      Serial.print(pin._closeState);
      Serial.print(" isOpen ");
      Serial.print(pin._isOpen);
      Serial.println();
    }
  }
}

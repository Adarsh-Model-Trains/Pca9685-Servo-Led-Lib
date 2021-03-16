/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#ifndef Pca9685_h
#define Pca9685_h

#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"

typedef struct {
  int _openState;
  int _closeState;
  bool _isOpen;
} Pca9685Pin;



class Pca9685 {

  private:
    char _type;
    int _defaultState;
    int _totalPins = 16;
    int _boardsAddress;
    int _pwmFrequency;
    bool * _pca9685PinStateList;
    Pca9685Pin * _pca9685PinList;
    Adafruit_PWMServoDriver _pwm;

    void refreshPin(int pinNo, Pca9685Pin pca9685Pin);
    void refreshPin(int pinNo, bool state);

  public:

    Pca9685() {
    }
    void initPca9685(char type);
    void setBoardAddress(int boardsAddress);
    void setPwmFrequency(int pwmFrequency);
    bool setSwitchOpenCloseRange(int pinNo, int openRange, int closeRange);
    bool throwSwitchPca9685Pin(int pinNo);
    bool closeSwitchPca9685Pin(int pinNo);
    bool switchOnPca9685Pin(int pinNo);
    bool switchOffPca9685Pin(int pinNo);
    void refreshPca9685Board();
    char getType();
    void resetPca9685Board();
    void displayPca9685();

    ~Pca9685() {
      delete [] _pca9685PinList;
    }
};
#endif

# Pca9685-Servo-Led-Lib

---


# <a href="https://github.com/adarshkumarsingh83/Pca9685-Servo-Led-Lib/archive/production.zip"> Library download link </a>


## About the Lib 
```

Pca9685-Servo-Led-Lib is for supporing multiple Pca9685 boards together 
in chain without complexcity of the programming 

max we can connect 64 Pca9685 together in chain which will give extra 1024 pins for operations 
this api support a simple interface where we can controll 1-1024 pins by its sequence number 
respected to their sequence in the chain 

pin number will start from 1 to (number of board X 16 pin per board)

NOTE:
- Order of Pca9685 board address wise must be in sequence otherwise it will not work in expected manner 
- First N sequence of board will assigne to the Servo type if number is passed in initPca9685Boards method 
  - N X 16 = No of pins will be avaiable for servo operations 
  - pin number will alwasy start from 1 to NX16 which is supplied for the servo 
- Secound N sequence of board will assigne to the Light type if number is passed in initPca9685Boards method  
  - N X 16 = No of pins will be avaiable for light operations 
  - pin number will always start from (Servo N pins)+1 to NX16 which is supplied for the lights
```




## Pca9685 board addressing configuration 

### YOUTUBE LINK BOARD DETAILS 
[![PCA9685-PWM-BOARD](http://img.youtube.com/vi/-SGKnX_kVgc/0.jpg)](https://www.youtube.com/watch?v=-SGKnX_kVgc "PCA9685-PWM-BOARD")

### YOUTUBE LINK SERVO CALIBRATION FOR OPEN AND THROW POSITION DETAILS 
[![SERVO-CALIBRATION-FOR-TURNOUT-PCA9685-PWM-BOARD](http://img.youtube.com/vi/DAPnm3rTAaE/0.jpg)](https://www.youtube.com/watch?v=DAPnm3rTAaE "SERVO-CALIBRATION-FOR-TURNOUT-PCA9685-PWM-BOARD")

![img](/image/pca9685-soldering-address-chart.png)



## steps for using lib

### YOUTUBE LINK LIBRARY DETAILS AND DEMO EXAMPLES PART 1
[![PCA9685-PWM-BOARD](http://img.youtube.com/vi/IK3555VY1DA/0.jpg)](https://www.youtube.com/watch?v=IK3555VY1DA "PCA9685-PWM-BOARD")


### YOUTUBE LINK LIBRARY DETAILS AND DEMO EXAMPLES PART 2
[![PCA9685-PWM-BOARD](http://img.youtube.com/vi/sMH5bc52cgc/0.jpg)](https://www.youtube.com/watch?v=sMH5bc52cgc "PCA9685-PWM-BOARD")


## include the header file
```
#include "Pca9685Board.h"
```

## define the object for the Pca9685Board
```
Pca9685Board pca9685Board;

```

## define the number of the board we are using in chain for servo 
```
#define NO_OF_SERVO_BOARDS 1 
```


## define the number of the board we are using in chain for led 
```
#define NO_OF_LIGHT_BOARDS 1
```


## initialize the object with in setup method for servo and led 
* pca9685Board.initPca9685Boards(NO_OF_SERVO_BOARDS, NO_OF_LIGHT_BOARDS);
* 
```
void setup() {
  
   .....

  pca9685Board.initPca9685Boards(NO_OF_SERVO_BOARDS, NO_OF_LIGHT_BOARDS);

  .......

}
```

## for debug messages a initialize Serial in setup
```
void setup() {
  
  Serial.begin(xxxx); // xxx can be any valid supported number 

  .........
}

```

## define the right and left max position for the servo switch moter in setup
* WE HAVE TO DO THIS FOR ALL THE  SERVVO TRUNOUT CONFIGURED 
* USE CALIBRATION SKETCH FOR KNOWING THE VALUE OF OPEN RANGE AND CLOSE RANGE
```
void setup() {
  
   .....

   pca9685Board.setSwitchRange(TURNOUT_NO, openRange, closeRange);

   .......

}

```

## set the frequency for the servo in setup 
* void setFrequencyTurnout(int pwmFrequencyTurnout);
* default is 50 

```
void setup() {
  
   .....

 pca9685Board.setFrequencyTurnout(60);

  .......

}
```

## set the frequency for the led in setup 
* void setFrequencyLight(int pwmFrequencyLight);
* default 1000

```
void setup() {
  
   .....

 pca9685Board.setFrequencyLight(1000);

  .......

}
```


## use lib method for switch on led
* pca9685Board.switchOn(pinNo);
* switchOn light will take pin number for switch on operation.
```
void loop() {
  
  .......

   pca9685Board.switchOn(pinNo);
  ..........
}
```


## use lib method for switch off led 
* pca9685Board.switchOff(pinNo);
* swtichOff light will take pin number for switch off operation 
```
void loop() {
  
  .......

	pca9685Board.switchOff(pinNo);
  ..........
}
```


## use lib method for throwing swtich for servo 
```
void loop() {
  
  .......

   pca9685Board.throwSwitch(pinNo);
  ..........
}
```

## use lib method for closing swtich for servo 
```
void loop() {
  
  .......

	pca9685Board.closeSwitch(pinNo);
  ..........
}
```

## use lib method for displaying state of pins 
```
void loop() {
  
  .......

	pca9685Board.displayPinState();
  ..........
}
```

## Connection details 
![img](/image/connections.JPG)
```
- sda and scl from arduino to 1st pca9685 
- external power supply +5v and gnd to the breadboard 
- from breadboard external power supply +5v and gnd to the first pca9685  in chain to vcc and gnd 
  and +5v and gnd to the 1st pca9685 sidew power inputs 
- gnd from the external power supply to the arduino gnd pin for common gnd setup 

# For Led Connection with pca9685
connect the jumper from yellow which is pwm pin to the breadboard 
then connect the resisot to that and followed by led long leg 
then connect the short leg of the led tot he common gnd in the breadboard 
repeate this for the other led in boards in chain 

# For Servo Connection with pca9685
connect the servo to the pca9685 but ensure below 
black wire to the black pin of the pca9685
red wire to the red pin of the pca9685
orange/yellow wire to the yellow pin of the pca9685

```


### Complete Example
* servo is on pca9685 1st board pin 0 
* led is on pca9685 2nd board pin 31 

```
#include "Pca9685Board.h"

#define NO_OF_SERVO_BOARDS 2
#define NO_OF_LIGHT_BOARDS 2

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
    pca9685Board.switchOn(pinNo + 32);
  }
  pca9685Board.displayPinState();
  delay(1000);
  for (int i = 1; i <= 32; i++) {
    int pinNo = i;
    pca9685Board.closeSwitch(pinNo);
    pca9685Board.switchOff(pinNo + 32);
  }
  pca9685Board.displayPinState();
  delay(1000);
}

```